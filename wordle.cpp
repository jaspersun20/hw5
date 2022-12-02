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
	set<string>& floatset,
	const std::set<std::string>& dict,
	std::set<std::string>& answers,
	string& fullword,
	string temp,
	size_t k);
void floatingHelper(
	const std::string& in,
	map< char, size_t > floatingmap,
	set<string>& floatset,
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
		map< char, size_t > floatingmap;
		map<char, size_t>::iterator it;
		for(size_t c=0; c<floating.length(); c++){
			it=floatingmap.find(floating[c]);
			if(it==floatingmap.end()){
				size_t num = 1;
				floatingmap[floating[c]]=num;
			}
			else{
				(it->second)++;
			}
		}
		floatingHelper(in, floatingmap,floatset, newfloating, floatword, i);
		set<string>::iterator it1;
		// for every word in floating set, fill in letters from alphabet
		for(it1=floatset.begin(); it1!=floatset.end();++it1){
			 string fullword = *it1;
			 string temp;
			 wordleHelper(in, floatset, dict, answers,fullword, temp, k);
		}
		return answers;
}

void floatingHelper(
	const std::string& in,
	map< char, size_t > floatingmap,
	set<string>& floatset,
 	std::string& newfloating,
	string floatword,
	size_t i){
		// base case: if the floating length reaches limit
		if(floatword.length()==in.length()){
			map<char, size_t>::iterator it;
			map<char, size_t>::iterator it1;
			for(it=floatingmap.begin(); it!=floatingmap.end();++it){
				size_t f = floatword.find(it->first);
				if(f==string::npos){
					return;
				}
				if(it->second>1){
					if(floatword.find(it->first,f+1)==string::npos){
						return;
					}
				}
			}
			// cout << floatword<<endl;
			floatset.insert(floatword);
			return;
		}
		else{
			// 
			if(in[i]=='-'){
				for(size_t j=0; j<newfloating.length(); j++){
					floatingHelper(in, floatingmap, floatset, newfloating, (floatword+newfloating[j]), i+1);
				}
			}
			else{
				char temp=in[i];
				floatingHelper(in, floatingmap, floatset, newfloating, (floatword+temp), i+1);
			}
		}
	}

void wordleHelper(
	const std::string& in,
	set<string>& floatset,
	const std::set<std::string>& dict,
	std::set<std::string>& answers,
	string& fullword,
	string temp,
	size_t k){
			// base case
			if(temp.length()==fullword.length()){
				// cout << temp<<endl;
				if(isValid(temp, dict)){		
				answers.insert(temp);
				return;
			}
			else{
				return;
			}
			}
			else{
				if(fullword[k]=='-'){
					for(int a=97; a<=122; a++){
						// cout <<"entered main helper"<<endl;
						wordleHelper(in,floatset, dict, answers,fullword, (temp+char(a)),k+1);
					}
				}
				else{
					wordleHelper(in,floatset, dict, answers, fullword, (temp+fullword[k]),k+1);
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
