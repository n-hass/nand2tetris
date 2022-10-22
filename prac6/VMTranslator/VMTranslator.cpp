#include <string>

#include "VMTranslator.h"
#include "Filestr.hpp"

using namespace std;

int VMTranslator::labelCount = 0;

// a single point of reference for decoding register reference
string VMTranslator::regDecode(string seg, int offset) {
    if (seg == "this")
        return "THIS";

    if (seg == "that")
        return "THAT";

    if (seg == "argument")
        return "ARG";
    
    if (seg == "local")
        return "LCL";
    
    if (seg == "static")
        return to_string(16+offset);

    if (seg == "pointer")
        return "R"+to_string(3 + offset);

    if (seg == "temp") 
        return "R"+to_string(5 + offset);

    if (seg == "constant")
        return to_string(offset);

    return "";
}

string VMTranslator::newLabelId() {
	string out = to_string(labelCount);
	labelCount++;
	return out;
}

bool VMTranslator::validSegment(string segment) {
    if (
        segment == "constant" || 
        segment == "static" || 
        segment == "local" || 
        segment == "this" ||
        segment == "that" ||
        segment == "temp" ||
        segment == "pointer" ||
        segment == "argument" )
    {
        return true;
    }
    return false;
}

string VMTranslator::fnLabelEncode(string name) {
	return "FUNC."+moduleName+"."+name;
}

string VMTranslator::fnLabelEncode(string modName, string name) {
	return "FUNC."+modName+"."+name;
}

/**
 * VMTranslator constructor
 */
VMTranslator::VMTranslator() {
  moduleName = "defMod";
}

VMTranslator::VMTranslator(string moduleName_in) {
  moduleName = moduleName_in;
}

/**
 * VMTranslator destructor
 */
VMTranslator::~VMTranslator() {
    // Your code here
}

/** Generate Hack Assembly code for a VM push operation */
string VMTranslator::vm_push(string segment, int offset) {
	if (validSegment(segment) == false)
		return "";

	Filestr out;
	string reg = regDecode(segment, offset);
	string ofs = to_string(offset);

	if (segment == "constant" || segment == "static" ||
			segment == "pointer" || segment == "temp") {
		out.ins(  "@" + reg, "push "+segment+" "+ofs );
		(segment=="constant") ? out.ins("D=A") : out.ins("D=M");
	} 
	else if (
		segment == "local" ||
		segment == "this" ||
		segment == "that" ||
		segment == "argument"
		)
	{
		out.ins(  "@" + reg, "push "+segment+" "+ofs );
		out.ins(  "D=M"    );
		out.ins(  "@"+ofs  );
		out.ins(  "A=D+A"  );
		out.ins(  "D=M"    );
	}

	out.ins(  "@SP"    );
	out.ins(  "A=M"    );
	out.ins(  "M=D"    );
	out.ins(  "@SP"    );
	out.ins(  "M=M+1"  );

	return out.str();
}

/** Generate Hack Assembly code for a VM pop operation */
string VMTranslator::vm_pop(string segment, int offset) {

	if (validSegment(segment) == false)
		return "";
	
	Filestr out;
	string reg = regDecode(segment, offset);
	string ofs = to_string(offset);

	if (segment == "constant") {
		// error
		return "";
	}
    
	out.ins(  "@" + reg, "pop "+segment+" "+ofs );

	if (segment == "static" || 
			segment == "temp" ||
			segment == "pointer") 
	{
		out.ins(  "D=A"    );
	}

	else if (
		segment == "local" || 
		segment == "this" ||
		segment == "that" ||
		segment == "argument" 
		) 
	{ // all the same
		out.ins(  "D=M"    );
		out.ins(  "@"+ofs  );
		out.ins(  "D=D+A"  );
	}

	out.ins(  "@R13"   );
	out.ins(  "M=D"    );
	out.ins(  "@SP"    );
	out.ins(  "AM=M-1" );
	out.ins(  "D=M"    );
	out.ins(  "@R13"   );
	out.ins(  "A=M"    );
	out.ins(  "M=D"    );

	return out.str();
}

/** Generate Hack Assembly code for a VM add operation */
string VMTranslator::vm_add() {
	Filestr out;

	out.ins("@SP","add");
	out.ins(  "AM=M-1"  ); // AM dest as stack is 1 entry smaller after op complete
	out.ins(  "D=M"     );
	out.ins(  "A=A-1"   );

	out.ins(  "M=M+D"   );

	return out.str();
}

/** Generate Hack Assembly code for a VM sub operation */
string VMTranslator::vm_sub() {
	Filestr out;

	out.ins("@SP","sub");
	out.ins(  "AM=M-1"  ); // AM dest as stack is 1 entry smaller after op complete
	out.ins(  "D=M"     );
	out.ins(  "A=A-1"   );

	out.ins(  "M=M-D"   );

	return out.str();
}

/** Generate Hack Assembly code for a VM neg operation */
string VMTranslator::vm_neg() {
  Filestr out;

	out.ins("@SP","neg");
	out.ins(  "A=M-1"  );

	out.ins(  "M=-M"   );

	return out.str();
}

/** Generate Hack Assembly code for a VM eq operation */
string VMTranslator::vm_eq() {
	Filestr out;
	string lID = newLabelId();

	out.ins("@SP","eq");
	out.ins(  "AM=M-1"  ); // AM dest as stack is 1 entry smaller after op complete
	out.ins(  "D=M"     );
	out.ins(  "A=A-1"   );

	out.ins(	"D=M-D"		);
	out.ins(	"@EQ.true_"+lID		);
	out.ins(	"D;JEQ"		);
	out.ins(	"@SP"			);
	out.ins(	"A=M-1"		);
	out.ins(	"M=0"		);
	out.ins(	"@EQ.skip_"+lID		);
	out.ins(	"0;JMP"		);
	out.ins(	"(EQ.true_"+lID+")"	);
	out.ins(	"@SP"		);
	out.ins(	"A=M-1"		);
	out.ins(	"M=-1"			);
	out.ins(	"(EQ.skip_"+lID+")"	);

	return out.str();
}

/** Generate Hack Assembly code for a VM gt operation */
string VMTranslator::vm_gt(){
	Filestr out;
	string lID = newLabelId();

	out.ins("@SP","gt");
	out.ins(  "AM=M-1"  ); // AM dest as stack is 1 entry smaller after op complete
	out.ins(  "D=M"     );
	out.ins(  "A=A-1"   );

	out.ins(	"D=M-D"		);
	out.ins(	"@GT.true_"+lID		);
	out.ins(	"D;JGT"		);
	out.ins(	"@SP"			);
	out.ins(	"A=M-1"		);
	out.ins(	"M=0"		);
	out.ins(	"@GT.skip_"+lID		);
	out.ins(	"0;JMP"		);
	out.ins(	"(GT.true_"+lID+")"	);
	out.ins(	"@SP"		);
	out.ins(	"A=M-1"		);
	out.ins(	"M=-1"			);
	out.ins(	"(GT.skip_"+lID+")"	);

	return out.str();
}

/** Generate Hack Assembly code for a VM lt operation */
string VMTranslator::vm_lt(){
	Filestr out;
	string lID = newLabelId();

	out.ins("@SP","lt");
	out.ins(  "AM=M-1"  ); // AM dest as stack is 1 entry smaller after op complete
	out.ins(  "D=M"     );
	out.ins(  "A=A-1"   );

	out.ins(	"D=M-D"		);
	out.ins(	"@LT.true_"+lID		);
	out.ins(	"D;JLT"		);
	out.ins(	"@SP"			);
	out.ins(	"A=M-1"		);
	out.ins(	"M=0"		);
	out.ins(	"@LT.skip_"+lID		);
	out.ins(	"0;JMP"		);
	out.ins(	"(LT.true_"+lID+")"	);
	out.ins(	"@SP"		);
	out.ins(	"A=M-1"		);
	out.ins(	"M=-1"			);
	out.ins(	"(LT.skip_"+lID+")"	);

	return out.str();
}

/** Generate Hack Assembly code for a VM and operation */
string VMTranslator::vm_and(){
	Filestr out;

	out.ins(	"@SP"			);
	out.ins(	"AM=M-1"	);
	out.ins(	"D=M"			);
	out.ins(	"A=A-1"		);
	out.ins(	"M=M&D"		);

	return out.str();
}

/** Generate Hack Assembly code for a VM or operation */
string VMTranslator::vm_or(){
	Filestr out;
	
	out.ins(	"@SP"			);
	out.ins(	"AM=M-1"	);
	out.ins(	"D=M"			);
	out.ins(	"A=A-1"		);
	out.ins(	"M=M|D"		);

	return out.str();
}

/** Generate Hack Assembly code for a VM not operation */
string VMTranslator::vm_not(){
	Filestr out;
	
	out.ins(	"@SP"			);
	out.ins(	"A=M-1"	  );
	out.ins(	"M=!M"		);

	return out.str();
}

/** Generate Hack Assembly code for a VM label operation */
string VMTranslator::vm_label(string label){
	Filestr out;

	out.ins(	"("+label+")", "new label: "+label	);

	return out.str();
}

/** Generate Hack Assembly code for a VM goto operation */
string VMTranslator::vm_goto(string label) {
	Filestr out;

	out.ins(	"@"+label,"jump to "+label	);
	out.ins(	"0;JMP"	 );

	return out.str();
}

/** Generate Hack Assembly code for a VM if-goto operation */
string VMTranslator::vm_if(string label){
	Filestr out;

	out.ins(	"@SP", "if-goto "+label	);
	out.ins(	"AM=M-1"	);
	out.ins(	"D=M"	  	);
	out.ins(	"@"+label	);
	out.ins(	"D;JNE"		);

	return out.str();
}

/** Generate Hack Assembly code for a VM function operation */
string VMTranslator::vm_function(string function_name, int n_vars){
	Filestr out;
	string fLabel = fnLabelEncode(function_name); // manually use "def" as the module name

	out.ins( "("+fLabel+")", "function declaration: "+function_name+" "+to_string(n_vars) );
	out.ins(	"@SP	");
	out.ins(	"A=M	");

	out.comment("clearing the stack for function: "+function_name);
	for (int i=0; i<n_vars; i++) {
		out.ins(	"M=0"			);
		out.ins(	"A=A+1"		);
	}

	out.ins(	"D=A"		);
	out.ins(	"@SP"		);
	out.ins(	"M=D"		);

	return out.str();
}

/** Generate Hack Assembly code for a VM call operation */
string VMTranslator::vm_call(string function_name, int n_args){
	Filestr out;
	string lID = newLabelId();

	out.comment("call "+function_name);
	out.comment("store callers pointers");
	// R13 = SP
	out.ins(	"@SP"	 );
	out.ins(	"D=M"	 );
	out.ins(	"@R13" );
	out.ins(	"M=D"  );
	// *(SP) = @RET
	out.ins(	"@RET."+lID		);
	out.ins(	"D=A"	 );
	out.ins(	"@SP"	 );
	out.ins(	"A=M"	 );
	out.ins(	"M=D"	 );
	// increment stack pointer
	out.ins(	"@SP"	 );
	out.ins(	"M=M+1"	);
	// *(SP) = LCL
	out.ins(	"@LCL","store LCL on stack"  );
	out.ins(	"D=M" 	);
	out.ins(	"@SP" 	);
	out.ins(	"A=M" 	);
	out.ins(	"M=D" 	);
	// increment stack pointer
	out.ins(	"@SP"	 );
	out.ins(	"M=M+1"	);
	// *(SP) = ARG
	out.ins(	"@ARG","store ARG on stack"  );
	out.ins(	"D=M" 	);
	out.ins(	"@SP" 	);
	out.ins(	"A=M" 	);
	out.ins(	"M=D" 	);
	// increment stack pointer
	out.ins(	"@SP"	 );
	out.ins(	"M=M+1"	);
	// *(SP) = THIS
	out.ins(	"@THIS","store THIS on stack"  );
	out.ins(	"D=M" 	);
	out.ins(	"@SP" 	);
	out.ins(	"A=M" 	);
	out.ins(	"M=D" 	);
	// increment stack pointer
	out.ins(	"@SP"	 );
	out.ins(	"M=M+1"	);
	// *(SP) = THAT
	out.ins(	"@THAT","store THAT on stack"  );
	out.ins(	"D=M" 	);
	out.ins(	"@SP" 	);
	out.ins(	"A=M" 	);
	out.ins(	"M=D" 	);
	// increment stack pointer
	out.ins(	"@SP"	 );
	out.ins(	"M=M+1"	);

	out.comment("setup ARG and LCL for callee");
	// ARG = R13 - n_vars
	out.ins(	"@R13","update ARG"  );
	out.ins(	"D=M" 		);
	out.ins(	"@"+to_string(n_args) );
	out.ins(	"D=D-A" 	);
	out.ins(	"@ARG" 		);
	out.ins(	"M=D"			);
	// LCL = SP
	out.ins(	"@SP","update LCL"  );
	out.ins(	"D=M" 		);
	out.ins(	"@LCL" 		);
	out.ins(	"M=D" 		);
	out.ins(	"@"+fnLabelEncode(function_name) 	);
	out.ins(	"0;JMP"		);
	out.ins(	"(RET."+lID	);

	return out.str();
}

/** Generate Hack Assembly code for a VM return operation */
string VMTranslator::vm_return() {
	Filestr out;
	out.comment("returning to caller");
	// R13 = *(LCL - 5)
	out.ins(	"@LCL"	);
	out.ins(	"D=M"	  );
	out.ins(	"@5"	  );
	out.ins(	"A=D-A"	);
	out.ins(	"D=M"	  );
	out.ins(	"@R13"	);
	out.ins(	"M=D"	  );
	// *(ARG) = *(SP - 1)
	out.ins(	"@SP"		);
	out.ins(	"A=M-1"	);
	out.ins(	"D=M"	  );
	out.ins(	"@ARG"	);
	out.ins(	"A=M"	  );
	out.ins(	"M=D"	  );
	// SP = ARG + 1
	out.ins(	"D=A+1"	 );
	out.ins(	"@SP"	   );
	out.ins(	"M=D"	   );
	// THAT = *(LCL - 1), LCL = LCL - 1
	out.ins(	"@LCL"	  );
	out.ins(	"AM=M-1"	);
	out.ins(	"D=M"	  	);
	out.ins(	"@THAT"	  );
	out.ins(	"M=D"	  	);
	// THIS = *(LCL - 1), LCL = LCL - 1
	out.ins(	"@LCL"	  );
	out.ins(	"AM=M-1"	);
	out.ins(	"D=M"	  	);
	out.ins(	"@THIS"	  );
	out.ins(	"M=D"	  	);
	// ARG = *(LCL - 1), LCL = LCL - 1
	out.ins(	"@LCL"	  );
	out.ins(	"AM=M-1"	);
	out.ins(	"D=M"	  	);
	out.ins(	"@ARG"	  );
	out.ins(	"M=D"	  	);
	// LCL = *(LCL - 1)
	out.ins(	"@LCL"	  );
	out.ins(	"A=M-1"		);
	out.ins(	"D=M"	  	);
	out.ins(	"@LCL"	  );
	out.ins(	"M=D"	  	);
	// jump back
	out.ins(	"@R13", "jump back to caller"	);
	out.ins(	"A=M"			);
	out.ins(	"0;JMP"		);

	return out.str();
}