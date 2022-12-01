// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(
	const std::string& in,
	const set<string>& floatset,
	const std::set<std::string>& dict,
	std::set<std::string>& answers,
	string& fullword,
	size_t k);
void floatingHelper(
	const std::string& in,
	const set<string>& floatset,
  std::string& newfloating,
	string floatword,
	size_t i);

bool isValid(const std::string& in, const std::set<std::string>& dict);
// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> answers;
		set<string> floatset;
		string newfloating = floating+'-';
		string floatword;
		string fullword;
    size_t i=0;
		size_t k=0;
		floatingHelper(in,floatset, newfloating , floatword, i);
		wordleHelper(in, floatset, dict, answers, fullword, k);
		return answers;
}

void floatingHelper(
	const std::string& in,
	 set<string>& floatset,
 std::string& newfloating,
	string floatword,
	size_t i){
		// base case: if the floating length reaches limit
		if(floatword.length()==in.length()&&floatword!=in){
			floatset.insert(floatword);
		}
		else{
			// 
			if(in[i]!='-'){
				for(size_t j=0; j<newfloating.length(); j++){
					floatingHelper(in, floatset, newfloating, (floatword+newfloating[j]), i+1);
				}
			}
			else{
				char temp=in[i];
				floatingHelper(in, floatset, newfloating, (floatword+temp), i+1);
			}
		}
	}

void wordleHelper(
	const std::string& in,
	const set<string>& floatset,
	const std::set<std::string>& dict,
	std::set<std::string>& answers,
	string& fullword,
	size_t k){
		// base case
		set<string>::iterator it;
		// for every word in floating set, fill in letters from alphabet
		for(it=floatset.begin(); it!=floatset.end();++it){
			fullword = *it;
			// base case
			if(k==in.length()){
				if(isValid(fullword, dict)){
				answers.insert(fullword);
				return;
			}
			else{
				return;
			}
			}
			else{
				if(fullword[k]=='-'){
					for(int a=97; a<=122; a++){
						fullword[k]=char(a);
						wordleHelper(in,floatset, dict, answers, fullword,k+1);
						fullword[k]=='-';
					}
				}
				else{
					wordleHelper(in,floatset, dict, answers, fullword,k+1);
				}
			}
	}
	}


bool isValid(const std::string& in, const std::set<std::string>& dict){
	set<string>::iterator it=dict.find(in);
	set<char>::iterator it1;
	if(it!=dict.end()){
		// cout<<"found in dict"<<endl;
			return true;
		}
	else{return false;}
}