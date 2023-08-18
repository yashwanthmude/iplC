#include "scanner.hh"
#include "parser.tab.hh"
#include <fstream>
#include <iostream>
#include <map>
#include <stack>
// #include "ast.hh"
using namespace std;

SymbTab gst, gstfun, gststruct;
string filename;
extern std::map<string, abstract_astnode *> ast;
std::map<std::string, datatype> predefined{
	{"printf", createtype(VOID_TYPE)},
	{"scanf", createtype(VOID_TYPE)},
	{"mod", createtype(INT_TYPE)}};
int main(int argc, char **argv)
{
	fstream in_file, out_file;

	in_file.open(argv[1], ios::in);

	IPL::Scanner scanner(in_file);

	IPL::Parser parser(scanner);

#ifdef YYDEBUG
	parser.set_debug_level(1);
#endif
	parser.parse();
	// create gstfun with function entries only

	for (const auto &entry : gst.Entries)
	{
		if (entry.second.varfun == "fun")
			gstfun.Entries.insert({entry.first, entry.second});
	}
	// create gststruct with struct entries only

	for (const auto &entry : gst.Entries)
	{
		if (entry.second.varfun == "struct")
			gststruct.Entries.insert({entry.first, entry.second});
	}
	
	extern vector<string> regvec;
	extern int regcount;
	extern int lc_count;
	extern int local_count_prev;
	extern vector<string>lcvec;
	extern map<string, int> offsetmap;
	extern int offset ;
	extern int jmpcount;
	extern int lastjmp;
	extern map<pair<string, string>, int> structmap;
	extern map<string,string> structdef;

	
	cout<<"\t.section\t.rodata"<<endl;
	cout<<"\t.text"<<endl;

	for(auto it = gststruct.Entries.begin(); it != gststruct.Entries.end(); ++it)
	{
		
		for(auto it2 = it->second.symbtab->Entries.begin(); it2 != it->second.symbtab->Entries.end(); ++it2)
		{
			structmap.insert({{it->first, it2->first}, it2->second.offset});
		}
		
		// it->second.symbtab->print();
		
	}
	//print structmap
	



	for (auto it = gstfun.Entries.begin(); it != gstfun.Entries.end(); ++it)
	{
		offsetmap.clear();
		offset = 0;
		regcount = 0;
		lastjmp = ++jmpcount;



		

		for (auto it2 = it->second.symbtab->Entries.begin(); it2 != it->second.symbtab->Entries.end(); ++it2)
		{
			if(it2->second.offset>0){
				offsetmap.insert({it2->first, it2->second.offset-4});
			}
			if(it2->second.offset<0){
				offsetmap.insert({it2->first, it2->second.offset});
				offset +=it2->second.size;
				
			}
			if(it2->second.type.type==STRUCT_TYPE){
				structdef.insert({it2->first,it2->second.type.structname});
			}

			
		}

		// it->second.symbtab->print();
		// ast[it->first]->print(0);
		//print local symbol table

	

		cout<<"\t.globl\t"<<it->first<<endl;
		cout<<"\t.type\t"<<it->first<<", @function"<<endl;
		
		cout<<it->first<<":"<<endl;
		cout<<"\tpushl\t%ebp"<<endl;
		cout<<"\tmovl\t%esp, %ebp"<<endl;
		cout<<"\tsubl\t$"<<offset<<", %esp"<<endl;
	
		ast[it->first]->gencode();
		cout<<".L"<<lastjmp<<":"<<endl;
		cout<<"\tnop"<<endl;
		cout<<"\tleave"<<endl;
		cout<<"\tret"<<endl;

		
		for(int i=local_count_prev;i<lc_count;i++)
		{
			cout<<".LC"<<i<<": "<<endl;
			cout<<"\t.string\t"<<lcvec[i]<<endl;
			local_count_prev=lc_count;
		}
	}

	fclose(stdout);
}
