#include "ast.hh"
#include <cstdarg>
#include <map>
#include <string>

vector<string> regvec = {"ebx", "ecx", "esi", "edi", "edx", "eax"};
int regcount = 0;
int lc_count = 0;
int local_count_prev = 0;
vector<string> lcvec;
map<string, int> offsetmap;
int offset = 0;
int jmpcount = 1;
int lastjmp;
int struct_offset;
map<pair<string, string>, int> structmap;
string struct_name;
int struct_depth = 0;
map<string, string> structdef;
int array_depth = 0;
int array_size = 4;
int b=0;

empty_astnode::empty_astnode() : statement_astnode()
{
	astnode_type = EmptyNode;
}

void empty_astnode::print(int ntabs)
{
	cout << "\"empty\"" << endl;
}

void empty_astnode::gencode()
{
}

//////////////////////////

seq_astnode::seq_astnode() : statement_astnode()
{

	astnode_type = SeqNode;
}

void seq_astnode::pushback(statement_astnode *child)
{
	children_nodes.push_back(child);
}

void seq_astnode::print(int ntabs)
{
	printblanks(ntabs);
	printAst("", "l", "seq", &children_nodes);
}
void seq_astnode::gencode()
{

	for (int i = 0; i < children_nodes.size(); i++)
	{
		children_nodes[i]->gencode();
	}
}

///////////////////////////////////

assignS_astnode::assignS_astnode(exp_astnode *l, exp_astnode *r, string tc) : statement_astnode()
{
	typecast = tc;
	left = l;
	right = r;
	id = "Ass";
	astnode_type = AssNode;
}

void assignS_astnode::print(int ntabs)
{
	printAst("assignS", "aa", "left", left, "right", right);
}
void assignS_astnode::gencode()
{

	if (left->astnode_type == IdentifierNode)
	{
		if (right->astnode_type == IntConstNode)
		{

			cout << "\tmovl\t$" << right->int_val << "," << offsetmap[left->idname()] << "(%ebp)" << endl;
		}
		else if (right->astnode_type == IdentifierNode)
		{
			cout << "\tmovl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
			cout << "\tmovl\t%eax," << offsetmap[left->idname()] << "(%ebp)" << endl;
		}
		else
		{
			right->gencode();
			cout << "\tmovl\t%eax," << offsetmap[left->idname()] << "(%ebp)" << endl;
		}
	}
	if (left->astnode_type == MemberNode)
	{
		left->gencode();
		int left_offset = struct_offset;

		if (right->astnode_type == IntConstNode)
		{
			cout << "\tmovl\t$" << right->int_val << "," << left_offset << "(%ebp)" << endl;
		}
		else if (right->astnode_type == IdentifierNode)
		{
			cout << "\tmovl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
			cout << "\tmovl\t%eax," << left_offset << "(%ebp)" << endl;
		}
		else
		{
			right->gencode();
			cout << "\tmovl\t%eax," << left_offset << "(%ebp)" << endl;
		}
	}
	if (left->astnode_type == OpUnaryNode)
	{
		if (left->idname() == "DEREF")
		{
			left->gencode();

			if (right->astnode_type == IntConstNode)
			{
				cout << "\tmovl\t$" << right->int_val << ",(%edx)" << endl;
			}
			else if (right->astnode_type == IdentifierNode)
			{
				cout << "\tmovl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
				cout << "\tmovl\t%eax,(%edx)" << endl;
			}
			else
			{
				regcount++;
				cout << "\tmovl\t%edx,%" << regvec[regcount - 1] << endl;
				right->gencode();
				cout << "\tmovl\t%eax,(%" << regvec[regcount - 1] << ")" << endl;
				regcount--;
			}
		}
	}
	if (left->astnode_type == ArrowNode)
	{	
		left->gencode();
		if (right->astnode_type == IntConstNode)
		{
			cout<<"\tmovl\t$"<<right->int_val<<","<<struct_offset<<"(%edx)"<<endl;
		}
		else if(right->astnode_type==IdentifierNode)
		{
			cout<<"\tmovl\t"<<offsetmap[right->idname()]<<"(%ebp),%eax"<<endl;
			cout<<"\tmovl\t%eax,"<<struct_offset<<"(%edx)"<<endl;
		}
		else
		{
			regcount++;
			cout<<"\tmovl\t%edx,%"<<regvec[regcount-1]<<endl;
			int temp_offset=struct_offset;
			right->gencode();
			cout<<"\tmovl\t%eax,"<<temp_offset<<"(%"<<regvec[regcount-1]<<")"<<endl;
			regcount--;
		}
	}
	if(left->astnode_type==	ArrayRefNode){
		left->gencode();
		if(right->astnode_type==IntConstNode)
		{
			if(b==0){
			cout<<"\tmovl\t$"<<right->int_val<<","<<"(%ebp,%edx,1)"<<endl;
			}
			if(b==1){
			cout<<"\tmovl\t$"<<right->int_val<<","<<"(%edx)"<<endl;
			}
		}
		else if(right->astnode_type==IdentifierNode)
		{
			cout<<"\tmovl\t"<<offsetmap[right->idname()]<<"(%ebp),%eax"<<endl;
			if(b==0){
			cout<<"\tmovl\t%eax,"<<"(%ebp,%edx,1)"<<endl;
			}
			if(b==1){
			cout<<"\tmovl\t%eax,"<<"(%edx)"<<endl;
			}

		}
		else{
			regcount++;
			cout<<"\tmovl\t%edx,%"<<regvec[regcount-1]<<endl;
			right->gencode();
			if(b==0){
			cout<<"\tmovl\t%eax,(%ebp,%"<<regvec[regcount-1]<<",1)"<<endl;
			}
			if(b==1){
			cout<<"\tmovl\t%eax,(%"<<regvec[regcount-1]<<")"<<endl;
			}

			regcount--;
		}
	}
}

///////////////////////////////////

return_astnode::return_astnode(exp_astnode *c) : statement_astnode()
{
	child = c;
	id = "Return";
	astnode_type = ReturnNode;
}
void return_astnode::print(int ntabs)
{
	printAst("", "a", "return", child);
}
void return_astnode::gencode()
{

	if (child->astnode_type == IntConstNode)
	{
		cout << "\tmovl\t$" << child->int_val << ",%eax" << endl;
	}
	else if (child->astnode_type == IdentifierNode)
	{
		cout << "\tmovl\t" << offsetmap[child->idname()] << "(%ebp),%eax" << endl;
	}
	else
	{
		child->gencode();
	}

	cout << "\tjmp\t.L" << lastjmp << endl;
}

////////////////////////////////////

if_astnode::if_astnode(exp_astnode *l, statement_astnode *m, statement_astnode *r) : statement_astnode()
{
	left = l;
	middle = m;
	right = r;
	id = "If";
	astnode_type = IfNode;
}

void if_astnode::print(int ntabs)
{
	printAst("if", "aaa",
			 "cond", left,
			 "then", middle,
			 "else", right);
}
void if_astnode::gencode()
{

	if (left->astnode_type == IntConstNode)
	{
		if (left->int_val == 0)
		{
			right->gencode();
		}
		else
		{
			middle->gencode();
		}
	}

	else if (left->astnode_type == IdentifierNode)
	{

		cout << "\tcmpl\t$0," << offsetmap[left->idname()] << "(%ebp)" << endl;

		cout << "\tje\t.L" << ++jmpcount << endl;

		int temp = jmpcount;

		middle->gencode();

		cout << "\tjmp\t.L" << ++jmpcount << endl;

		int temp1 = jmpcount;

		cout << "\t.L" << temp << ":" << endl;

		right->gencode();

		cout << "\t.L" << temp1 << ":" << endl;
	}
	else
	{
		left->gencode();

		cout << "\tcmpl\t$0,%eax" << endl;

		cout << "\tje\t.L" << ++jmpcount << endl;

		int temp = jmpcount;

		middle->gencode();

		cout << "\tjmp\t.L" << ++jmpcount << endl;

		int temp1 = jmpcount;

		cout << ".L" << temp << ":" << endl;

		right->gencode();

		cout << ".L" << temp1 << ":" << endl;
	}
}
////////////////////////////////////

while_astnode::while_astnode(exp_astnode *l, statement_astnode *r) : statement_astnode()
{
	left = l;
	right = r;
	id = "While";
	astnode_type = WhileNode;
}

void while_astnode::print(int ntabs)
{
	printAst("while", "aa",
			 "cond", left,
			 "stmt", right);
}
void while_astnode::gencode()
{

	if (left->astnode_type == IntConstNode)
	{
		if (left->int_val != 0)
		{
			cout << ".L" << ++jmpcount << ":" << endl;
			int temp = jmpcount;
			right->gencode();

			cout << "\tjmp\t.L" << temp << endl;
		}
	}
	else if (left->astnode_type == IdentifierNode)
	{
		cout << "\tjmp\t.L" << ++jmpcount << endl;
		cout << "\t.L" << ++jmpcount << ":" << endl;
		int temp = jmpcount;
		right->gencode();
		cout << ".L" << temp - 1 << ":" << endl;
		cout << "\tcmpl\t$0," << offsetmap[left->idname()] << "(%ebp)" << endl;
		cout << "\tjne\t.L" << temp << endl;
	}
	else
	{

		cout << "\tjmp\t.L" << ++jmpcount << endl;
		cout << ".L" << ++jmpcount << ":" << endl;
		int temp = jmpcount;
		right->gencode();
		cout << ".L" << temp - 1 << ":" << endl;
		left->gencode();
		cout << "\tcmpl\t$0,%eax" << endl;
		cout << "\tjne\t.L" << temp << endl;
	}
}
/////////////////////////////////

for_astnode::for_astnode(exp_astnode *l, exp_astnode *m1, exp_astnode *m2, statement_astnode *r) : statement_astnode()
{
	left = l;
	middle1 = m1;
	middle2 = m2;
	right = r;
	id = "For";
	astnode_type = ForNode;
}

void for_astnode::print(int ntabs)
{
	printAst("for", "aaaa",
			 "init", left,
			 "guard", middle1,
			 "step", middle2,
			 "body", right);
}
void for_astnode::gencode()
{

	left->gencode();

	cout << "\tjmp\t.L" << ++jmpcount << endl;
	cout << ".L" << ++jmpcount << ":" << endl;

	int temp = jmpcount;
	right->gencode();
	middle2->gencode();
	cout << ".L" << temp - 1 << ":" << endl;

	middle1->gencode();

	cout << "\tcmpl\t$0,%eax" << endl;

	cout << "\tjne\t.L" << temp << endl;
}

//////////////////////////////////

// exp_astnode::exp_astnode() : abstract_astnode()
// {
// }

//////////////////////////////////
string exp_astnode::idname()
{
	return id;
};

op_binary_astnode::op_binary_astnode(string val, exp_astnode *l, exp_astnode *r) : exp_astnode()
{
	id = val;
	left = l;
	right = r;
	astnode_type = OpBinaryNode;
}

void op_binary_astnode::print(int ntabs)
{
	string str = "\"" + id + "\"";
	char *str1 = const_cast<char *>(str.c_str());
	printAst("op_binary", "saa", "op", str1, "left", left, "right", right);
}
void op_binary_astnode::gencode()
{

	if ((left->astnode_type != OpBinaryNode && left->astnode_type != OpUnaryNode && left->astnode_type != FunCallNode && left->astnode_type != MemberNode && left->astnode_type != ArrowNode && left->astnode_type!= ArrayRefNode) && (right->astnode_type != OpBinaryNode && right->astnode_type != OpUnaryNode && right->astnode_type != FunCallNode && right->astnode_type != MemberNode && right->astnode_type != ArrowNode && right->astnode_type!= ArrayRefNode))
	{

		if (left->astnode_type == IntConstNode && right->astnode_type == IntConstNode)
		{

			if (id == "PLUS_INT")
			{
				cout << "\tmovl\t$" << left->int_val + right->int_val << ",%eax" << endl;
			}
			if (id == "MINUS_INT")
			{

				cout << "\tmovl\t$" << left->int_val - right->int_val << ",%eax" << endl;
			}
			if (id == "MULT_INT")
			{

				cout << "\tmovl\t$" << left->int_val * right->int_val << ",%eax" << endl;
			}
			if (id == "DIV_INT")
			{
				cout << "\tmovl\t$" << left->int_val / right->int_val << ",%eax" << endl;
			}
			if (id == "GE_OP_INT")
			{

				if (left->int_val >= right->int_val)
				{

					cout << "\tmovl\t$1,%eax" << endl;
				}
				else
				{
					cout << "\tmovl\t$0,%eax" << endl;
				}
			}
			if (id == "GT_OP_INT")
			{
				if (left->int_val > right->int_val)
				{
					cout << "\tmovl\t$1,%eax" << endl;
				}
				else
				{
					cout << "\tmovl\t$0,%eax" << endl;
				}
			}
			if (id == "LE_OP_INT")
			{
				if (left->int_val <= right->int_val)
				{
					cout << "\tmovl\t$1,%eax" << endl;
				}
				else
				{
					cout << "\tmovl\t$0,%eax" << endl;
				}
			}
			if (id == "LT_OP_INT")
			{
				if (left->int_val < right->int_val)
				{
					cout << "\tmovl\t$1,%eax" << endl;
				}
				else
				{
					cout << "\tmovl\t$0,%eax" << endl;
				}
			}
			if (id == "EQ_OP_INT")
			{
				if (left->int_val == right->int_val)
				{
					cout << "\tmovl\t$1,%eax" << endl;
				}
				else
				{
					cout << "\tmovl\t$0,%eax" << endl;
				}
			}
			if (id == "NE_OP_INT")
			{
				if (left->int_val != right->int_val)
				{
					cout << "\tmovl\t$1,%eax" << endl;
				}
				else
				{
					cout << "\tmovl\t$0,%eax" << endl;
				}
			}
			if (id == "OR_OP")
			{
				if (left->int_val != 0 || right->int_val != 0)
				{
					cout << "\tmovl\t$1,%eax" << endl;
				}
				else
				{
					cout << "\tmovl\t$0,%eax" << endl;
				}
			}
			if (id == "AND_OP")
			{
				if (left->int_val != 0 && right->int_val != 0)
				{
					cout << "\tmovl\t$1,%eax" << endl;
				}
				else
				{
					cout << "\tmovl\t$0,%eax" << endl;
				}
			}
		}
		else if (left->astnode_type == IntConstNode && right->astnode_type == IdentifierNode)
		{

			if (id == "PLUS_INT")
			{
				cout << "\tmovl\t$" << left->int_val << ",%eax" << endl;
				cout << "\taddl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
			}
			if (id == "MINUS_INT")
			{
				cout << "\tmovl\t$" << left->int_val << ",%eax" << endl;
				cout << "\tsubl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
			}
			if (id == "MULT_INT")
			{

				cout << "\tmovl\t$" << left->int_val << ",%eax" << endl;
				cout << "\timull\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
			}
			if (id == "DIV_INT")
			{

				cout << "\tmovl\t$" << left->int_val << ",%eax" << endl;
				cout << "\tcdq" << endl;
				cout << "\tidivl\t" << offsetmap[right->idname()] << "(%ebp)" << endl;
			}
			if (id == "GE_OP_INT")
			{

				cout << "\tmovl\t$" << left->int_val << "%eax" << endl;
				cout << "\tcmpl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
				cout << "\tsetge\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "GT_OP_INT")
			{

				cout << "\tmovl\t$" << left->int_val << ",%eax" << endl;
				cout << "\tcmpl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
				cout << "\tsetg\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "LE_OP_INT")
			{

				cout << "\tmovl\t$" << left->int_val << ",%eax" << endl;
				cout << "\tcmpl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
				cout << "\tsetle\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "LT_OP_INT")
			{

				cout << "\tmovl\t$" << left->int_val << ",%eax" << endl;
				cout << "\tcmpl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
				cout << "\tsetl\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "EQ_OP_INT")
			{

				cout << "\tmovl\t$" << left->int_val << ",%eax" << endl;
				cout << "\tcmpl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
				cout << "\tsete\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "NE_OP_INT")
			{

				cout << "\tmovl\t$" << left->int_val << ",%eax" << endl;
				cout << "\tcmpl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
				cout << "\tsetne\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "OR_OP")
			{

				if (left->int_val != 0)
				{

					cout << "\tmovl\t$1,%eax" << endl;
				}
				else
				{

					cout << "\tcmpl\t$0,%" << offsetmap[right->idname()] << "(%ebp)" << endl;
					cout << "\tsetne\t%al" << endl;
					cout << "\tmovzbl\t%al,%eax" << endl;
				}
			}
			if (id == "AND_OP")
			{

				if (left->int_val != 0)
				{

					cout << "\tcmpl\t$0,%" << offsetmap[right->idname()] << "(%ebp)" << endl;

					cout << "\tstene\t%al" << endl;
					cout << "\tmovzbl\t%al,%eax" << endl;
				}
				else
				{

					cout << "\tmovl\t$0,%eax" << endl;
				}
			}
		}
		else if (left->astnode_type == IdentifierNode && right->astnode_type == IntConstNode)
		{

			if (id == "PLUS_INT")
			{
				cout << "\tmovl\t" << offsetmap[left->idname()] << "(%ebp),%eax" << endl;
				cout << "\taddl\t$" << right->int_val << ",%eax" << endl;
			}
			if (id == "MINUS_INT")
			{
				cout << "\tmovl\t" << offsetmap[left->idname()] << "(%ebp),%eax" << endl;
				cout << "\tsubl\t$" << right->int_val << ",%eax" << endl;
			}
			if (id == "MULT_INT")
			{
				cout << "\tmovl\t" << offsetmap[left->idname()] << "(%ebp),%eax" << endl;
				cout << "\timull\t$" << right->int_val << ",%eax" << endl;
			}
			if (id == "DIV_INT")
			{

				cout << "\tmovl\t" << offsetmap[left->idname()] << "(%ebp),%eax" << endl;
				cout << "\tcdq" << endl;
				regcount++;
				cout << "\tmovl\t$" << right->int_val << ",%" << regvec[regcount - 1] << endl;
				cout << "\tidivl\t%" << regvec[regcount - 1] << endl;
				regcount--;
			}
			if (id == "GE_OP_INT")
			{
				cout << "\tmovl\t$" << right->int_val << ",%eax" << endl;
				cout << "\tcmpl\t%eax," << offsetmap[left->idname()] << "(%ebp)" << endl;
				cout << "\tsetge\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "GT_OP_INT")
			{
				cout << "\tmovl\t$" << right->int_val << ",%eax" << endl;
				cout << "\tcmpl\t%eax," << offsetmap[left->idname()] << "(%ebp)" << endl;
				cout << "\tsetg\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "LE_OP_INT")
			{
				cout << "\tmovl\t$" << right->int_val << ",%eax" << endl;
				cout << "\tcmpl\t%eax," << offsetmap[left->idname()] << "(%ebp)" << endl;
				cout << "\tsetle\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "LT_OP_INT")
			{
				cout << "\tmovl\t$" << right->int_val << ",%eax" << endl;
				cout << "\tcmpl\t%eax," << offsetmap[left->idname()] << "(%ebp)" << endl;
				cout << "\tsetl\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "EQ_OP_INT")
			{
				cout << "\tmovl\t$" << right->int_val << ",%eax" << endl;
				cout << "\tcmpl\t%eax," << offsetmap[left->idname()] << "(%ebp)" << endl;
				cout << "\tsete\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "NE_OP_INT")
			{
				cout << "\tmovl\t$" << right->int_val << ",%eax" << endl;
				cout << "\tcmpl\t%eax," << offsetmap[left->idname()] << "(%ebp)" << endl;
				cout << "\tsetne\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "OR_OP")
			{

				if (right->int_val != 0)
				{

					cout << "\tmovl\t$1,%eax" << endl;
				}
				else
				{

					cout << "\tcmpl\t$0,%" << offsetmap[left->idname()] << "(%ebp)" << endl;
					cout << "\tsetne\t%al" << endl;
					cout << "\tmovzbl\t%al,%eax" << endl;
				}
			}
			if (id == "AND_OP")
			{

				if (right->int_val != 0)
				{

					cout << "\tcmpl\t$0,%" << offsetmap[left->idname()] << "(%ebp)" << endl;
					cout << "\tsetne\t%al" << endl;
					cout << "\tmovzbl\t%al,%eax" << endl;
				}
				else
				{
					cout << "\tmovl\t$0,%eax" << endl;
				}
			}
		}
		else
		{

			if (id == "PLUS_INT")
			{

				cout << "\tmovl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
				cout << "\taddl\t" << offsetmap[left->idname()] << "(%ebp),%eax" << endl;
			}
			if (id == "MINUS_INT")
			{

				cout << "\tmovl\t" << offsetmap[left->idname()] << "(%ebp),%eax" << endl;
				cout << "\tsubl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
			}
			if (id == "MULT_INT")
			{

				cout << "\tmovl\t" << offsetmap[left->idname()] << "(%ebp),%eax" << endl;
				cout << "\timull\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
			}
			if (id == "DIV_INT")
			{

				cout << "\tmovl\t" << offsetmap[left->idname()] << "(%ebp),%eax" << endl;
				cout << "\tcdq" << endl;
				cout << "\tidivl\t" << offsetmap[right->idname()] << "(%ebp)" << endl;
			}
			if (id == "GE_OP_INT")
			{

				cout << "\tmovl\t" << offsetmap[left->idname()] << "(%ebp),%eax" << endl;
				cout << "\tcmpl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
				cout << "\tsetge\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "GT_OP_INT")
			{

				cout << "\tmovl\t" << offsetmap[left->idname()] << "(%ebp),%eax" << endl;
				cout << "\tcmpl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
				cout << "\tsetg\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "LE_OP_INT")
			{

				cout << "\tmovl\t" << offsetmap[left->idname()] << "(%ebp),%eax" << endl;
				cout << "\tcmpl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
				cout << "\tsetle\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "LT_OP_INT")
			{

				cout << "\tmovl\t" << offsetmap[left->idname()] << "(%ebp),%eax" << endl;
				cout << "\tcmpl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
				cout << "\tsetl\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "EQ_OP_INT")
			{

				cout << "\tmovl\t" << offsetmap[left->idname()] << "(%ebp),%eax" << endl;
				cout << "\tcmpl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
				cout << "\tsete\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "NE_OP_INT")
			{

				cout << "\tmovl\t" << offsetmap[left->idname()] << "(%ebp),%eax" << endl;
				cout << "\tcmpl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
				cout << "\tsetne\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "OR_OP")
			{

				cout << "\tmovl\t" << offsetmap[left->idname()] << "(%ebp),%eax" << endl;
				cout << "\torl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
				cout << "\tcmpl\t$0,%eax" << endl;
				cout << "\tsetne\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "AND_OP")
			{

				cout << "\tmovl\t" << offsetmap[left->idname()] << "(%ebp),%eax" << endl;
				cout << "\tandl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
				cout << "\tcmpl\t$0,%eax" << endl;
				cout << "\tsetne\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
		}
	}
	else if ((left->astnode_type != OpBinaryNode && left->astnode_type != OpUnaryNode && left->astnode_type != FunCallNode && left->astnode_type != MemberNode && left->astnode_type != ArrowNode && left->astnode_type != ArrayRefNode) && (right->astnode_type == OpBinaryNode || right->astnode_type == OpUnaryNode || right->astnode_type == FunCallNode || right->astnode_type == MemberNode || right->astnode_type == ArrowNode || right->astnode_type == ArrayRefNode))
	{

		if (left->astnode_type == IdentifierNode)
		{

			if (id == "PLUS_INT")
			{
				right->gencode();
				cout << "\taddl\t" << offsetmap[left->idname()] << "(%ebp),%eax" << endl;
			}
			if (id == "MULT_INT")
			{
				right->gencode();
				cout << "\timull\t" << offsetmap[left->idname()] << "(%ebp),%eax" << endl;
			}
			if (id == "MINUS_INT")
			{
				right->gencode();
				cout << "\tsubl\t" << offsetmap[left->idname()] << "(%ebp),%eax" << endl;
			}
			if (id == "DIV_INT")
			{

				right->gencode();
				regcount++;
				cout << "\tmovl\t%eax,%" << regvec[regcount - 1] << endl;
				cout << "\tmovl\t" << offsetmap[left->idname()] << "(%ebp),%eax" << endl;
				cout << "\tcdq" << endl;
				cout << "\tidivl\t%" << regvec[regcount - 1] << endl;
				regcount--;
			}
			if (id == "GE_OP_INT")
			{
				right->gencode();
				cout << "\tcmpl\t%eax," << offsetmap[left->idname()] << "(%ebp)" << endl;
				cout << "\tsetge\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "GT_OP_INT")
			{
				right->gencode();
				cout << "\tcmpl\t%eax," << offsetmap[left->idname()] << "(%ebp)" << endl;
				cout << "\tsetg\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "LE_OP_INT")
			{
				right->gencode();
				cout << "\tcmpl\t%eax," << offsetmap[left->idname()] << "(%ebp)" << endl;
				cout << "\tsetle\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "LT_OP_INT")
			{
				right->gencode();
				cout << "\tcmpl\t%eax," << offsetmap[left->idname()] << "(%ebp)" << endl;
				cout << "\tsetl\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "EQ_OP_INT")
			{
				right->gencode();
				cout << "\tcmpl\t%eax," << offsetmap[left->idname()] << "(%ebp)" << endl;
				cout << "\tsete\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "NE_OP_INT")
			{
				right->gencode();
				cout << "\tcmpl\t%eax," << offsetmap[left->idname()] << "(%ebp)" << endl;
				cout << "\tsetne\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "OR_OP")
			{
				cout << "\tcmpl\t$0," << offsetmap[left->idname()] << "(%ebp)" << endl;
				cout << "\tjne\t.L" << ++jmpcount << endl;
				int temp = jmpcount;
				right->gencode();
				cout << "\tcmpl\t$0,%eax" << endl;
				cout << "\tjne\t.L" << temp << endl;
				cout << "\tmovl\t$0,%eax" << endl;
				cout << "\tjmp\t.L" << ++jmpcount << endl;
				cout << ".L" << temp << ":" << endl;
				cout << "\tmovl\t$1,%eax" << endl;
				cout << ".L" << jmpcount << ":" << endl;
			}
			if (id == "AND_OP")
			{
				cout << "\tcmpl\t$0," << offsetmap[left->idname()] << "(%ebp)" << endl;
				cout << "\tje\t.L" << ++jmpcount << endl;
				int temp = jmpcount;
				right->gencode();
				cout << "\tcmpl\t$0,%eax" << endl;
				cout << "\tje\t.L" << temp << endl;
				cout << "\tmovl\t$1,%eax" << endl;
				cout << "\tjmp\t.L" << ++jmpcount << endl;
				cout << ".L" << temp << ":" << endl;
				cout << "\tmovl\t$0,%eax" << endl;
				cout << ".L" << jmpcount << ":" << endl;
			}
		}
		else
		{

			if (id == "PLUS_INT")
			{
				right->gencode();
				cout << "\taddl\t$" << left->int_val << ",%eax" << endl;
			}
			if (id == "MULT_INT")
			{
				right->gencode();
				cout << "\timull\t$" << left->int_val << ",%eax" << endl;
			}
			if (id == "MINUS_INT")
			{
				right->gencode();
				cout << "\tsubl\t$" << left->int_val << ",%eax" << endl;
			}
			if (id == "DIV_INT")
			{
				right->gencode();
				regcount++;
				cout << "\tmovl\t%eax,%" << regvec[regcount - 1] << endl;
				cout << "\tmovl\t$" << left->int_val << ",%eax" << endl;
				cout << "\tcdq" << endl;
				cout << "\tidivl\t%" << regvec[regcount - 1] << endl;
				regcount--;
			}
			if (id == "GE_OP_INT")
			{
				right->gencode();
				cout << "\tcmpl\t%eax,$" << left->int_val << endl;
				cout << "\tsetge\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "GT_OP_INT")
			{
				right->gencode();
				cout << "\tcmpl\t%eax,$" << left->int_val << endl;
				cout << "\tsetg\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "LE_OP_INT")
			{
				right->gencode();
				cout << "\tcmpl\t%eax,$" << left->int_val << endl;
				cout << "\tsetle\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "LT_OP_INT")
			{
				right->gencode();
				cout << "\tcmpl\t%eax,$" << left->int_val << endl;
				cout << "\tsetl\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "EQ_OP_INT")
			{
				right->gencode();
				cout << "\tcmpl\t%eax,$" << left->int_val << endl;
				cout << "\tsete\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "NE_OP_INT")
			{
				right->gencode();
				cout << "\tcmpl\t%eax,$" << left->int_val << endl;
				cout << "\tsetne\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "OR_OP")
			{
				if (left->int_val == 0)
				{
					right->gencode();
					cout << "\tcmpl\t$0,%eax" << endl;
					cout << "\tsetne\t%al" << endl;
					cout << "\tmovzbl\t%al,%eax" << endl;
				}
				else
				{
					cout << "\tmovl\t$1,%eax" << endl;
				}
			}
			if (id == "AND_OP")
			{
				if (left->int_val == 0)
				{
					cout << "\tmovl\t$0,%eax" << endl;
				}
				else
				{
					right->gencode();
					cout << "\tcmpl\t$0,%eax" << endl;
					cout << "\tsetne\t%al" << endl;
					cout << "\tmovzbl\t%al,%eax" << endl;
				}
			}
		}
	}
	else if ((left->astnode_type == OpBinaryNode || left->astnode_type == OpUnaryNode || left->astnode_type == FunCallNode || left->astnode_type == MemberNode || left->astnode_type == ArrowNode || left->astnode_type == ArrayRefNode) && (right->astnode_type != OpBinaryNode && right->astnode_type != OpUnaryNode && right->astnode_type != FunCallNode && right->astnode_type != MemberNode && right->astnode_type != ArrowNode && right->astnode_type != ArrayRefNode))
	{
		if (right->astnode_type == IdentifierNode)
		{

			if (id == "PLUS_INT")
			{

				left->gencode();
				cout << "\taddl\t" << offsetmap[right->idname()] << "(%ebp),  %eax" << endl;
			}
			if (id == "MULT_INT")
			{
				left->gencode();
				cout << "\timull\t" << offsetmap[right->idname()] << "(%ebp),  %eax" << endl;
			}
			if (id == "MINUS_INT")
			{
				left->gencode();
				cout << "\tsubl\t" << offsetmap[right->idname()] << "(%ebp),  %eax" << endl;
			}
			if (id == "DIV_INT")
			{
				left->gencode();
				cout << "\tcdq" << endl;
				regcount++;
				cout << "\tmovl\t" << offsetmap[right->idname()] << "(%ebp),%" << regvec[regcount - 1] << endl;
				cout << "\tidivl\t%" << regvec[regcount - 1] << endl;
				regcount--;
			}
			if (id == "GE_OP_INT")
			{
				left->gencode();
				cout << "\tcmpl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
				cout << "\tsetge\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "GT_OP_INT")
			{
				left->gencode();
				cout << "\tcmpl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
				cout << "\tsetg\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "LE_OP_INT")
			{
				left->gencode();
				cout << "\tcmpl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
				cout << "\tsetle\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "LT_OP_INT")
			{
				left->gencode();
				cout << "\tcmpl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
				cout << "\tsetl\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "EQ_OP_INT")
			{
				left->gencode();
				cout << "\tcmpl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
				cout << "\tsete\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "NE_OP_INT")
			{
				left->gencode();
				cout << "\tcmpl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
				cout << "\tsetne\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "OR_OP")
			{
				cout << "\tcmpl\t$0," << offsetmap[right->idname()] << "(%ebp)" << endl;
				cout << "\tjne\t.L" << ++jmpcount << endl;
				int temp = jmpcount;
				left->gencode();
				cout << "\tcmpl\t$0,%eax" << endl;
				cout << "\tjne\t.L" << temp << endl;
				cout << "\tmovl\t$0,%eax" << endl;
				cout << "\tjmp\t.L" << ++jmpcount << endl;
				cout << ".L" << temp << ":" << endl;
				cout << "\tmovl\t$1,%eax" << endl;
				cout << ".L" << jmpcount << ":" << endl;
			}
			if (id == "AND_OP")
			{
				cout << "\tcmpl\t$0," << offsetmap[right->idname()] << "(%ebp)" << endl;
				cout << "\tje\t.L" << ++jmpcount << endl;
				int temp = jmpcount;
				left->gencode();
				cout << "\tcmpl\t$0,%eax" << endl;
				cout << "\tje\t.L" << temp << endl;
				cout << "\tmovl\t$1,%eax" << endl;
				cout << "\tjmp\t.L" << ++jmpcount << endl;
				cout << ".L" << temp << ":" << endl;
				cout << "\tmovl\t$0,%eax" << endl;
				cout << ".L" << jmpcount << ":" << endl;
			}
		}
		else
		{

			if (id == "PLUS_INT")
			{

				left->gencode();
				cout << "\taddl\t$" << right->int_val << ",%eax" << endl;
			}
			if (id == "MULT_INT")
			{
				left->gencode();
				cout << "\timull\t$" << right->int_val << ",%eax" << endl;
			}
			if (id == "MINUS_INT")
			{
				left->gencode();
				cout << "\tsubl\t$" << right->int_val << ",%eax" << endl;
			}
			if (id == "DIV_INT")
			{
				left->gencode();
				cout << "\tcdq" << endl;
				regcount++;
				cout << "\tmovl\t$" << right->int_val << ",%" << regvec[regcount - 1] << endl;
				cout << "\tidivl\t%" << regvec[regcount - 1] << endl;
				regcount--;
			}
			if (id == "GE_OP_INT")
			{
				left->gencode();
				cout << "\tcmpl\t$" << right->int_val << ",%eax" << endl;
				cout << "\tsetge\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "GT_OP_INT")
			{
				left->gencode();
				cout << "\tcmpl\t$" << right->int_val << ",%eax" << endl;
				cout << "\tsetg\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "LE_OP_INT")
			{
				left->gencode();
				cout << "\tcmpl\t$" << right->int_val << ",%eax" << endl;
				cout << "\tsetle\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "LT_OP_INT")
			{
				left->gencode();
				cout << "\tcmpl\t$" << right->int_val << ",%eax" << endl;
				cout << "\tsetl\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "EQ_OP_INT")
			{
				left->gencode();
				cout << "\tcmpl\t$" << right->int_val << ",%eax" << endl;
				cout << "\tsete\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "NE_OP_INT")
			{
				left->gencode();
				cout << "\tcmpl\t$" << right->int_val << ",%eax" << endl;
				cout << "\tsetne\t%al" << endl;
				cout << "\tmovzbl\t%al,%eax" << endl;
			}
			if (id == "OR_OP")
			{
				if (right->int_val == 0)
				{
					left->gencode();
					cout << "\tcmpl\t$0,%eax" << endl;
					cout << "\tsetne\t%al" << endl;
					cout << "\tmovzbl\t%al,%eax" << endl;
				}
				else
				{
					cout << "\tmovl\t$1,%eax" << endl;
				}
			}
			if (id == "AND_OP")
			{
				if (right->int_val == 0)
				{
					cout << "\tmovl\t$0,%eax" << endl;
				}
				else
				{
					left->gencode();
					cout << "\tcmpl\t$0,%eax" << endl;
					cout << "\tsetne\t%al" << endl;
					cout << "\tmovzbl\t%al,%eax" << endl;
				}
			}
		}
	}

	else if ((left->astnode_type == OpBinaryNode || left->astnode_type == OpUnaryNode || left->astnode_type == FunCallNode || left->astnode_type == MemberNode || left->astnode_type == ArrowNode || left->astnode_type == ArrayRefNode) && (right->astnode_type == OpBinaryNode || right->astnode_type == OpUnaryNode || right->astnode_type == FunCallNode || right->astnode_type == MemberNode || right->astnode_type == ArrowNode || right->astnode_type == ArrayRefNode))
	{

		if (id == "PLUS_INT")
		{
			left->gencode();
			regcount++;
			cout << "\tmovl\t%eax,%" << regvec[regcount - 1] << endl;
			right->gencode();
			cout << "\taddl\t%" << regvec[regcount - 1] << ",%eax" << endl;
			regcount--;
		}
		if (id == "MULT_INT")
		{
			left->gencode();
			regcount++;
			cout << "\tmovl\t%eax,%" << regvec[regcount - 1] << endl;
			right->gencode();
			cout << "\timull\t%" << regvec[regcount - 1] << ",%eax" << endl;
			regcount--;
		}
		if (id == "MINUS_INT")
		{
			left->gencode();
			regcount++;
			cout << "\tmovl\t%eax,%" << regvec[regcount - 1] << endl;
			right->gencode();
			cout << "\tsubl\t%eax,%" << regvec[regcount - 1] << endl;
			cout << "\tmovl\t%" << regvec[regcount - 1] << ",%eax" << endl;
			regcount--;
		}
		if (id == "DIV_INT")
		{
			right->gencode();
			regcount++;
			cout << "\tmovl\t%eax,%" << regvec[regcount - 1] << endl;
			left->gencode();
			cout << "\tcdq" << endl;
			cout << "\tidivl\t%" << regvec[regcount - 1] << endl;
			regcount--;
		}
		if (id == "GE_OP_INT")
		{
			left->gencode();
			regcount++;
			cout << "\tmovl\t%eax,%" << regvec[regcount - 1] << endl;
			right->gencode();
			cout << "\tcmpl\t%eax,%" << regvec[regcount - 1] << endl;
			cout << "\tsetge\t%al" << endl;
			cout << "\tmovzbl\t%al,%eax" << endl;
			regcount--;
		}
		if (id == "GT_OP_INT")
		{
			left->gencode();
			regcount++;
			cout << "\tmovl\t%eax,%" << regvec[regcount - 1] << endl;
			right->gencode();
			cout << "\tcmpl\t%eax,%" << regvec[regcount - 1] << endl;
			cout << "\tsetg\t%al" << endl;
			cout << "\tmovzbl\t%al,%eax" << endl;
			regcount--;
		}
		if (id == "LE_OP_INT")
		{
			left->gencode();
			regcount++;
			cout << "\tmovl\t%eax,%" << regvec[regcount - 1] << endl;
			right->gencode();
			cout << "\tcmpl\t%eax,%" << regvec[regcount - 1] << endl;
			cout << "\tsetle\t%al" << endl;
			cout << "\tmovzbl\t%al,%eax" << endl;
			regcount--;
		}
		if (id == "LT_OP_INT")
		{
			left->gencode();
			regcount++;
			cout << "\tmovl\t%eax,%" << regvec[regcount - 1] << endl;
			right->gencode();
			cout << "\tcmpl\t%eax,%" << regvec[regcount - 1] << endl;
			cout << "\tsetl\t%al" << endl;
			cout << "\tmovzbl\t%al,%eax" << endl;
			regcount--;
		}
		if (id == "EQ_OP_INT")
		{
			left->gencode();
			regcount++;
			cout << "\tmovl\t%eax,%" << regvec[regcount - 1] << endl;
			right->gencode();
			cout << "\tcmpl\t%eax,%" << regvec[regcount - 1] << endl;
			cout << "\tsete\t%al" << endl;
			cout << "\tmovzbl\t%al,%eax" << endl;
			regcount--;
		}
		if (id == "NE_OP_INT")
		{
			left->gencode();
			regcount++;
			cout << "\tmovl\t%eax,%" << regvec[regcount - 1] << endl;
			right->gencode();
			cout << "\tcmpl\t%eax,%" << regvec[regcount - 1] << endl;
			cout << "\tsetne\t%al" << endl;
			cout << "\tmovzbl\t%al,%eax" << endl;
			regcount--;
		}
		if (id == "OR_OP")
		{
			left->gencode();
			cout << "\tcmpl\t$0,%eax" << endl;
			cout << "\tjne\t.L" << ++jmpcount << endl;
			int temp = jmpcount;
			right->gencode();
			cout << "\tcmpl\t$0,%eax" << endl;
			cout << "\tjne\t.L" << temp << endl;
			cout << "\tmovl\t$0,%eax" << endl;
			cout << "\tjmp\t.L" << ++jmpcount << endl;
			cout << ".L" << temp << ":" << endl;
			cout << "\tmovl\t$1,%eax" << endl;
			cout << ".L" << jmpcount << ":" << endl;
		}
		if (id == "AND_OP")
		{
			left->gencode();
			cout << "\tcmpl\t$0,%eax" << endl;
			cout << "\tje\t.L" << ++jmpcount << endl;
			int temp = jmpcount;
			right->gencode();
			cout << "\tcmpl\t$0,%eax" << endl;
			cout << "\tje\t.L" << temp << endl;
			cout << "\tmovl\t$1,%eax" << endl;
			cout << "\tjmp\t.L" << ++jmpcount << endl;
			cout << ".L" << temp << ":" << endl;
			cout << "\tmovl\t$0,%eax" << endl;
			cout << ".L" << jmpcount << ":" << endl;
		}
	}
}

///////////////////////////////////

op_unary_astnode::op_unary_astnode(string val) : exp_astnode()
{
	id = val;
	astnode_type = OpUnaryNode;
}

void op_unary_astnode::print(int ntabs)

{
	string str = "\"" + id + "\"";
	char *str1 = const_cast<char *>(str.c_str());
	printAst("op_unary", "sa", "op", str1, "child", child);
}

op_unary_astnode::op_unary_astnode(string val, exp_astnode *l) : exp_astnode()
{
	id = val;
	child = l;
	astnode_type = OpUnaryNode;
}

string op_unary_astnode::getoperator()
{
	return id;
}
void op_unary_astnode::gencode()
{

	if (id == "UMINUS")
	{
		if (child->astnode_type == IntConstNode)
		{
			cout << "\tmovl\t$" << -1 * child->int_val << ",%eax" << endl;
		}
		else if (child->astnode_type == IdentifierNode)
		{
			cout << "\tmovl\t" << offsetmap[child->idname()] << "(%ebp),%eax" << endl;
			cout << "\tnegl\t%eax" << endl;
		}
		else
		{
			child->gencode();
			cout << "\tnegl\t%eax" << endl;
		}
	}
	if (id == "NOT")
	{

		if (child->astnode_type == IntConstNode)
		{
			if (child->int_val == 0)
				cout << "\tmovl\t$1,%eax" << endl;
			else
				cout << "\tmovl\t$0,%eax" << endl;
		}
		else if (child->astnode_type == IdentifierNode)
		{
			cout << "\tmovl\t" << offsetmap[child->idname()] << "(%ebp),%eax" << endl;
			cout << "\tcmpl\t$0,%eax" << endl;
			cout << "\tsete\t%al" << endl;
			cout << "\tmovzbl\t%al,%eax" << endl;
		}
		else
		{
			child->gencode();
			cout << "\tcmpl\t$0,%eax" << endl;
			cout << "\tsete\t%al" << endl;
			cout << "\tmovzbl\t%al,%eax" << endl;
		}
	}
	if (id == "PP")
	{
		if (child->astnode_type == IdentifierNode)
		{
			cout << "\tmovl\t" << offsetmap[child->idname()] << "(%ebp),%eax" << endl;
			cout << "\taddl\t$1," << offsetmap[child->idname()] << "(%ebp)" << endl;
		}
		else
		{
			child->gencode();
			cout << "\taddl\t$1," << struct_offset << "(%ebp)" << endl;
		}
	}
	if (id == "ADDRESS")
	{
		if (child->astnode_type == IdentifierNode)
		{
			cout << "\tleal\t" << offsetmap[child->idname()] << "(%ebp),%eax" << endl;
		}
		else
		{
			child->gencode();
			cout << "\tleal\t%eax,%eax" << endl;
		}
	}
	if (id == "DEREF")
	{
		if (child->astnode_type == IdentifierNode)
		{
			cout << "\tmovl\t" << offsetmap[child->idname()] << "(%ebp),%eax" << endl;
			cout << "\tmovl\t%eax,%edx" << endl;
			cout << "\tmovl\t(%eax),%eax" << endl;
		}
		else
		{
			child->gencode();
			cout << "\tmovl\t%eax,%edx" << endl;
			cout << "\tmovl\t(%eax),%eax" << endl;
		}
	}
}
///////////////////////////////////

assignE_astnode::assignE_astnode(exp_astnode *l, exp_astnode *r) : exp_astnode()
{
	left = l;
	right = r;
	astnode_type = AssignNode;
}

void assignE_astnode::print(int ntabs)
{
	printAst("assignE", "aa", "left", left, "right", right);
}

void assignE_astnode::gencode()
{

	if (right->astnode_type == IntConstNode)
	{
		cout << "\tmovl\t$" << right->int_val << "," << offsetmap[left->idname()] << "(%ebp)" << endl;
	}
	else if (right->astnode_type == IdentifierNode)
	{
		cout << "\tmovl\t" << offsetmap[right->idname()] << "(%ebp),%eax" << endl;
		cout << "\tmovl\t%eax," << offsetmap[left->idname()] << "(%ebp)" << endl;
	}
	else
	{
		right->gencode();
		cout << "\tmovl\t%eax," << offsetmap[left->idname()] << "(%ebp)" << endl;
	}
}

///////////////////////////////////

funcall_astnode::funcall_astnode() : exp_astnode()
{
	astnode_type = FunCallNode;
}

funcall_astnode::funcall_astnode(identifier_astnode *child)
{
	funcname = child;
	astnode_type = FunCallNode;
}

void funcall_astnode::setname(string name)
{
	funcname = new identifier_astnode(name);
}

void funcall_astnode::pushback(exp_astnode *subtree)
{
	children.push_back(subtree);
}

void funcall_astnode::print(int ntabs)
{
	printAst("funcall", "al", "fname", funcname, "params", &children);
}
void funcall_astnode::gencode()
{
	int countparams = children.size();
	vector<string> funparams;
	int beforeregcount = regcount;

	for (int i = 0; i < countparams; i++)
	{
		//struct with size greater than 4 bytes
		
		if (children[i]->data_type.type == STRUCT_TYPE && children[i]->data_type.size()>4)
		{	
			int funcall_offset = offsetmap[children[i]->idname()];
			string funcall_type = structdef[children[i]->idname()];
			int funcall_count = 0;
			for (auto it = structmap.begin(); it != structmap.end(); it++)
			{
				if (it->first.first == funcall_type)
				{
					funcall_count++;
				}
			}
			for (int i = funcall_count - 1; i >= 0; i--)
			{
				funparams.push_back(to_string((funcall_offset + 4 * i)) + "(%ebp)");
			}
		}
		//if its a identifer of an array
		else if (children[i]->data_type.type == TYPE_ARRAY_REF && children[i]->astnode_type== IdentifierNode)
		{
			regcount++;
			cout<<"\tleal\t"<<offsetmap[children[i]->idname()]<<"(%ebp),%"<<regvec[regcount-1]<<endl;
			funparams.push_back("%" + regvec[regcount - 1]);

		}
		
		else if (children[i]->astnode_type == IntConstNode)
		{
			funparams.push_back("$" + to_string(children[i]->int_val));
		}
		else if (children[i]->astnode_type == IdentifierNode)
		{
			funparams.push_back(to_string(offsetmap[children[i]->idname()]) + "(%ebp)");
		}

		else if (children[i]->astnode_type == StringConstNode)
		{
			funparams.push_back("$" + children[i]->idname());
		}
		else
		{
			children[i]->gencode();
			regcount++;
			cout << "\tmovl\t%eax,%" << regvec[regcount - 1] << endl;
			funparams.push_back("%" + regvec[regcount - 1]);
		}
	}

	for (int i = 0; i < funparams.size(); i++)
	{
		cout << "\tpushl\t" << funparams[i] << endl;
	}

	cout << "\tcall\t" << funcname->idname() << endl;

	regcount = beforeregcount;

	cout << "\taddl\t$" << 4 * countparams << ",%esp" << endl;
}

proccall_astnode::proccall_astnode(funcall_astnode *fc)
{
	procname = fc->funcname;
	children = fc->children;
}
void proccall_astnode::print(int ntabs)
{
	printAst("proccall", "al", "fname", procname, "params", &children);
}
void proccall_astnode::gencode()
{

	// cout<<procname->idname()<<endl;
	// procname->gencode();
	if (procname->idname() == "printf")
	{
		int printcount = 0;
		vector<string> printvec;

		for (int i = children.size() - 1; i >= 0; i--)
		{
			children[i]->gencode();
			if (children[i]->astnode_type == StringConstNode)
			{
				printvec.push_back("$.LC" + to_string(lc_count));
				// cout<<"\tpushl\t$.LC"<<lc_count<<endl;
				lc_count++;
			}
			else if (children[i]->astnode_type == IdentifierNode)
			{
				printvec.push_back(to_string(offsetmap[children[i]->idname()]) + "(%ebp)");
				// cout<<"\tpushl\t"<<offsetmap[children[i]->idname()]<<"(%ebp)"<<endl;
			}
			else if (children[i]->astnode_type == IntConstNode)
			{
				printvec.push_back("$" + to_string(children[i]->int_val));
				// cout<<"\tpushl\t$"<<children[i]->int_val<<endl;
			}
			else
			{
				regcount++;
				cout << "\tmovl\t%eax,%" << regvec[regcount - 1] << endl;
				printvec.push_back("%" + regvec[regcount - 1]);
			}

			printcount++;
		}

		for (int i = 0; i < printvec.size(); i++)
		{
			cout << "\tpushl\t" << printvec[i] << endl;
		}
		cout << "\tcall\tprintf" << endl;
		cout << "\taddl\t$" << 4 * printcount << ",%esp" << endl;
		regcount = 0;
	}
	else
	{
		int countparams = children.size();
		vector<string> funparams;
		int beforeregcount = regcount;

		for (int i = 0; i < countparams; i++)
		{

			if (children[i]->data_type.type == STRUCT_TYPE)
			{
				int funcall_offset = offsetmap[children[i]->idname()];
				string funcall_type = structdef[children[i]->idname()];
				int funcall_count = 0;
				for (auto it = structmap.begin(); it != structmap.end(); it++)
				{
					if (it->first.first == funcall_type)
					{
						funcall_count++;
					}
				}
				for (int i = funcall_count - 1; i >= 0; i--)
				{
					funparams.push_back(to_string((funcall_offset + 4 * i)) + "(%ebp)");
				}
			}
			else if (children[i]->astnode_type == IntConstNode)
			{
				funparams.push_back("$" + to_string(children[i]->int_val));
			}
			else if (children[i]->astnode_type == IdentifierNode)
			{
				funparams.push_back(to_string(offsetmap[children[i]->idname()]) + "(%ebp)");
			}

			else if (children[i]->astnode_type == StringConstNode)
			{
				funparams.push_back("$" + children[i]->idname());
			}
			else
			{
				children[i]->gencode();
				regcount++;
				cout << "\tmovl\t%eax,%" << regvec[regcount - 1] << endl;
				funparams.push_back("%" + regvec[regcount - 1]);
			}
		}

		for (int i = 0; i < funparams.size(); i++)
		{
			cout << "\tpushl\t" << funparams[i] << endl;
		}

		cout << "\tcall\t" << procname->idname() << endl;

		regcount = beforeregcount;

		cout << "\taddl\t$" << 4 * countparams << ",%esp" << endl;
	}
}
/////////////////////////////////////

intconst_astnode::intconst_astnode(int val) : exp_astnode()
{
	value = val;
	astnode_type = IntConstNode;
}

void intconst_astnode::print(int ntabs)
{

	printAst("", "i", "intconst", value);
}
void intconst_astnode::gencode()
{
}
/////////////////////////////////////
floatconst_astnode::floatconst_astnode(float val) : exp_astnode()
{
	value = val;
	astnode_type = FloatConstNode;
}

void floatconst_astnode::print(int ntabs)
{
	printAst("", "f", "floatconst", value);
}
void floatconst_astnode::gencode()
{
}
///////////////////////////////////
stringconst_astnode::stringconst_astnode(string val) : exp_astnode()
{
	value = val;
	astnode_type = StringConstNode;
}

void stringconst_astnode::print(int ntabs)
{
	printAst("", "s", "stringconst", stringTocharstar(value));
}
void stringconst_astnode::gencode()
{

	lcvec.push_back(value);
}

// ref_astnode::ref_astnode() : exp_astnode()
// {
// 	lvalue = true;
// }

/////////////////////////////////

identifier_astnode::identifier_astnode(string val) : ref_astnode()
{
	id = val;
	astnode_type = IdentifierNode;
}

void identifier_astnode::print(int ntabs)
{
	string str = "\"" + id + "\"";
	char *str1 = const_cast<char *>(str.c_str());
	printAst("", "s", "identifier", str1);
}
void identifier_astnode::gencode()
{
}

////////////////////////////////

arrayref_astnode::arrayref_astnode(exp_astnode *l, exp_astnode *r) : ref_astnode() // again, changed from ref to exp
{
	left = l;
	right = r;
	id = "ArrayRef";
	astnode_type = ArrayRefNode;

}

void arrayref_astnode::print(int ntabs)
{
	printAst("arrayref", "aa", "array", left, "index", right);
}
void arrayref_astnode::gencode()
{
	
	if(left->astnode_type == IdentifierNode){
		array_size = this->data_type.size();
		if(offsetmap[left->idname()] < 0)
		{
			cout<<"\tmovl\t$"<<offsetmap[left->idname()]<<",%eax"<<endl;
			b=0;
		}
		else{
			cout<<"\tmovl\t"<<offsetmap[left->idname()]<<"(%ebp),%eax"<<endl;
			b=1;
		}
		if(right->astnode_type == IntConstNode){
			
			cout<<"\taddl\t$"<<right->int_val*array_size<<",%eax"<<endl;
		}
		else if(right->astnode_type == IdentifierNode){
			// cout<<"\tmovl\t$"<<offsetmap[left->idname()]<<",%eax"<<endl;
			regcount++;
			cout<<"\tmovl\t"<<offsetmap[right->idname()]<<"(%ebp),%"<<regvec[regcount-1]<<endl;
			cout<<"\timull\t$"<<array_size<<",%"<<regvec[regcount-1]<<endl;
			cout<<"\taddl\t%"<<regvec[regcount-1]<<",%eax"<<endl;
			regcount--;
		}
		else{
			// cout<<"\tmovl\t$"<<offsetmap[left->idname()]<<",%eax"<<endl;
			regcount++;
			cout<<"\tmovl\t%eax,%"<<regvec[regcount-1]<<endl;
			int beforedepth = array_depth;
			int temp_b=b;
			array_depth=0;
			right->gencode();
			array_depth = beforedepth;
			b=temp_b;
			array_size = this->data_type.size();
			cout<<"\timull\t$"<<array_size<<",%eax"<<endl;
			cout<<"\taddl\t%"<<regvec[regcount-1]<<",%eax"<<endl;
			regcount--;

		}
	}
	else{
		array_depth++;
		left->gencode();
		array_depth--;
		array_size = this->data_type.size();


		if(right->astnode_type==IntConstNode){
			cout<<"\taddl\t$"<<right->int_val*array_size<<",%eax"<<endl;
		}
		else if(right->astnode_type==IdentifierNode){
			regcount++;
			cout<<"\tmovl\t"<<offsetmap[right->idname()]<<"(%ebp),%"<<regvec[regcount-1]<<endl;
			cout<<"\timull\t$"<<array_size<<",%"<<regvec[regcount-1]<<endl;
			cout<<"\taddl\t%"<<regvec[regcount-1]<<",%eax"<<endl;
			regcount--;

		}
		else{
			regcount++;
			cout<<"\tmovl\t%eax,%"<<regvec[regcount-1]<<endl;
			int beforedepth = array_depth;
			array_depth=0;
			int temp_b=b;
			right->gencode();
			b=temp_b;
			array_depth = beforedepth;
			array_size = this->data_type.size();
			cout<<"\timull\t$"<<array_size<<",%eax"<<endl;
			cout<<"\taddl\t%"<<regvec[regcount-1]<<",%eax"<<endl;
			regcount--;
		}
		
	}
	if(array_depth==0){

		if(b==0){
			cout<<"\tmovl\t%eax,%edx"<<endl;
			cout<<"\tmovl\t(%ebp,%eax,1),%eax"<<endl;
		}
		if(b==1){
			cout<<"\tmovl\t%eax,%edx"<<endl;
			cout<<"\tmovl\t(%eax),%eax"<<endl;
		}
	}




	
}



deref_astnode::deref_astnode(ref_astnode *c) : ref_astnode()
{
	child = c;
	id = "Deref";
	astnode_type = DerefNode;
}

void deref_astnode::print(int ntabs)
{
	printAst("", "a", "deref", child);
}
void deref_astnode::gencode()
{
	cout << "deref_astnode jasdhfjhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"<<endl;
	child->gencode();
}

/////////////////////////////////

member_astnode::member_astnode(exp_astnode *l, identifier_astnode *r) // change from ref to exp(1st arg)
{
	left = l;
	right = r;
	astnode_type = MemberNode;
}

void member_astnode::print(int ntabs)
{

	printAst("member", "aa", "struct", left, "field", right);
}
void member_astnode::gencode()
{
	if (left->astnode_type == IdentifierNode)
	{
		struct_offset = offsetmap[left->idname()];
		struct_name = structdef[left->idname()];
	}
	else
	{
		struct_depth++;
		left->gencode();
		struct_depth--;
	}
	pair<string, string> p = make_pair(struct_name, right->idname());
	struct_offset += structmap[p];
	struct_name = right->idname();
	if (struct_depth == 0)
	{
		cout << "\tmovl\t" << struct_offset << "(%ebp),%eax" << endl;
	}
}

/////////////////////////////////

arrow_astnode::arrow_astnode(exp_astnode *l, identifier_astnode *r)
{
	left = l;
	right = r;
	astnode_type = ArrowNode;
}

void arrow_astnode::print(int ntabs)
{

	printAst("arrow", "aa", "pointer", left, "field", right);
}
void arrow_astnode::gencode()
{
	cout << "\tmovl\t" << offsetmap[left->idname()] << "(%ebp),%eax" << endl;
	string a = structdef[left->idname()];
	// remove all the * from the string
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] == '*')
		{
			a.erase(i, 1);
		}
	}
	pair<string, string> p = make_pair(a, right->idname());
	struct_offset = structmap[p];
	cout<<"\tmovl\t%eax,%edx"<<endl;
	cout << "\tmovl\t" << struct_offset << "(%eax),%eax" << endl;
}
void printblanks(int blanks)
{
	for (int i = 0; i < blanks; i++)
		cout << " ";
}

/////////////////////////////////

void printAst(const char *astname, const char *fmt...) // fmt is a format string that tells about the type of the arguments.
{
	typedef vector<abstract_astnode *> *pv;
	va_list args;
	va_start(args, fmt);
	if ((astname != NULL) && (astname[0] != '\0'))
	{
		cout << "{ ";
		cout << "\"" << astname << "\""
			 << ": ";
	}
	cout << "{" << endl;
	while (*fmt != '\0')
	{
		if (*fmt == 'a')
		{
			char *field = va_arg(args, char *);
			abstract_astnode *a = va_arg(args, abstract_astnode *);
			cout << "\"" << field << "\": " << endl;

			a->print(0);
		}
		else if (*fmt == 's')
		{
			char *field = va_arg(args, char *);
			char *str = va_arg(args, char *);
			cout << "\"" << field << "\": ";

			cout << str << endl;
		}
		else if (*fmt == 'i')
		{
			char *field = va_arg(args, char *);
			int i = va_arg(args, int);
			cout << "\"" << field << "\": ";

			cout << i;
		}
		else if (*fmt == 'f')
		{
			char *field = va_arg(args, char *);
			double f = va_arg(args, double);
			cout << "\"" << field << "\": ";
			cout << f;
		}
		else if (*fmt == 'l')
		{
			char *field = va_arg(args, char *);
			pv f = va_arg(args, pv);
			cout << "\"" << field << "\": ";
			cout << "[" << endl;
			for (int i = 0; i < (int)f->size(); ++i)
			{
				(*f)[i]->print(0);
				if (i < (int)f->size() - 1)
					cout << "," << endl;
				else
					cout << endl;
			}
			cout << endl;
			cout << "]" << endl;
		}
		++fmt;
		if (*fmt != '\0')
			cout << "," << endl;
	}
	cout << "}" << endl;
	if ((astname != NULL) && (astname[0] != '\0'))
		cout << "}" << endl;
	va_end(args);
}

char *stringTocharstar(string str)
{
	char *charstar = const_cast<char *>(str.c_str());
	return charstar;
}

void gencode()
{
	// need to print assembly code whenever printf  is called
}
