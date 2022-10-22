#include <string>

#include "VMTranslator.h"
#include "Lines.hpp"

using namespace std;

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

/**
 * VMTranslator constructor
 */
VMTranslator::VMTranslator() {
    // Your code here
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

    File out;
    string reg = regDecode(segment, offset);
    string ofs = to_string(offset);

    if (segment == "constant" || segment == "static") {
    	out.ins(  "@" + reg, "push "+segment+" "+ofs );
    	(segment=="static") ? out.ins("D=M") : out.ins("D=A");
    } else {
			if (
					segment == "local" ||
					segment == "this" ||
					segment == "that" ||
					segment == "argument" ||
					segment == "local"
				)
			{
				out.ins(  "@" + reg, "push "+segment+" "+ofs );
				out.ins(  "D=M"    );
				out.ins(  "@"+ofs  );
				out.ins(  "A=D+A"  );
      }
			else if (segment == "pointer" || segment == "temp") {
				out.ins(  "@" + reg, "push "+segment+" "+ofs );
			}

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
	
	File out;
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
string VMTranslator::vm_add(){
    return "";
}

/** Generate Hack Assembly code for a VM sub operation */
string VMTranslator::vm_sub(){
    return "";
}

/** Generate Hack Assembly code for a VM neg operation */
string VMTranslator::vm_neg(){
    return "";
}

/** Generate Hack Assembly code for a VM eq operation */
string VMTranslator::vm_eq(){
    return "";
}

/** Generate Hack Assembly code for a VM gt operation */
string VMTranslator::vm_gt(){
    return "";
}

/** Generate Hack Assembly code for a VM lt operation */
string VMTranslator::vm_lt(){
    return "";
}

/** Generate Hack Assembly code for a VM and operation */
string VMTranslator::vm_and(){
    return "";
}

/** Generate Hack Assembly code for a VM or operation */
string VMTranslator::vm_or(){
    return "";
}

/** Generate Hack Assembly code for a VM not operation */
string VMTranslator::vm_not(){
    return "";
}

/** Generate Hack Assembly code for a VM label operation */
string VMTranslator::vm_label(string label){
    return "";
}

/** Generate Hack Assembly code for a VM goto operation */
string VMTranslator::vm_goto(string label){
    return "";
}

/** Generate Hack Assembly code for a VM if-goto operation */
string VMTranslator::vm_if(string label){
    return "";
}

/** Generate Hack Assembly code for a VM function operation */
string VMTranslator::vm_function(string function_name, int n_vars){
    return "";
}

/** Generate Hack Assembly code for a VM call operation */
string VMTranslator::vm_call(string function_name, int n_args){
    return "";
}

/** Generate Hack Assembly code for a VM return operation */
string VMTranslator::vm_return(){
    return "";
}