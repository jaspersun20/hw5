

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool solverHelper(const size_t k, const size_t n, const size_t dailyNeed, size_t row, size_t col, map<Worker_T, size_t> maxMap, DailySchedule& sched, const size_t maxShifts, const AvailabilityMatrix& avail);
bool isValid(size_t row, Worker_T col, const size_t maxShifts, const AvailabilityMatrix& avail, map<Worker_T, size_t> maxMap, const DailySchedule& sched, const size_t n, const size_t dailyNeed, const size_t k);
// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    size_t n = avail.size();
    size_t k = avail[0].size();
    size_t row=0;
    size_t col=0;
		for(unsigned int i=0; i<n; i++){
			vector<Worker_T> vec(dailyNeed, k);
			sched.push_back(vec);
		}
		map<Worker_T, size_t> maxMap;
    for(Worker_T c=0; c<k; c++){
        size_t zer=0;
        maxMap[c]=zer;
    }
    if(solverHelper(k, n, dailyNeed,row, col, maxMap, sched, maxShifts, avail)){
        return true;
    }
    else{
        return false;
    }
}

bool solverHelper(const size_t k, const size_t n, const size_t dailyNeed, size_t row, size_t col, map<Worker_T, size_t> maxMap, DailySchedule& sched, const size_t maxShifts, const AvailabilityMatrix& avail){
    // base case: if the day# runs out of order in sched matrix
    if(row == n) {
			return true;
			}
    // fill in every worker ID
    if(sched[row][col]==k){
    for(Worker_T workerID=0; workerID<k; workerID++){
			sched[row][col]=workerID;
			// if the worker id is valid
			if(isValid(row, workerID, maxShifts, avail, maxMap,sched, n, dailyNeed,k)){
					// if the number of workers needed is full
					if(col==dailyNeed){
							// recursion: solverHelper(row+1, col)
							if(solverHelper(k, n, dailyNeed, row+1, 0, maxMap, sched, maxShifts, avail)==true){
								return true;
							}
					}
					// if not full
					else{
							// recursion: solverHelper(row, col+1)
							if(solverHelper(k, n, dailyNeed,row, col+1, maxMap, sched, maxShifts, avail)==true){
									return true;
							}
					}
			}
    }
		// backtracking step
    sched[row][col]=k;
		}
	
		else{
			// if the number of workers needed is full
			if(col==dailyNeed){
					// recursion: solverHelper(row+1, col)
					if(solverHelper(k, n, dailyNeed, row+1, 0, maxMap, sched, maxShifts, avail)==true){
						return true;
					}
			}
			// if not full
			else{
					// recursion: solverHelper(row, col+1)
					if(solverHelper(k, n, dailyNeed,row, col+1, maxMap, sched, maxShifts, avail)==true){
							return true;
					}
			}
		}

    // if no solution found return false
    return false;
}

bool isValid(size_t row, Worker_T col, const size_t maxShifts, const AvailabilityMatrix& avail, map<Worker_T, size_t> maxMap, const DailySchedule& sched, const size_t n, const size_t dailyNeed, const size_t k){
		// check if one row contains same value
		vector<Worker_T> rvec = sched[row];
		map<Worker_T,int> rowmap;
		map<Worker_T,int>::iterator it;
		for(size_t i=0; i < rvec.size(); i++){
			it=rowmap.find(rvec[i]);
			if(it==rowmap.end()){
				rowmap[rvec[i]]=1;
			}
			else{
				rowmap[rvec[i]]++;
				if(rvec[i]!=k){
				return false;
				}
			}
		}
		// check max shift
		map<Worker_T, size_t> mMap;
    for(Worker_T c=0; c<k; c++){
        size_t zer=0;
        mMap[c]=zer;
    }
		for(size_t x=0;x<n;x++){
			for(size_t y=0; y<dailyNeed;y++){
				(mMap[sched[x][y]])++;
			}
		}
		map<Worker_T, size_t>::iterator it1;
		for(it1=mMap.begin();it1!=mMap.end();++it1){
			if(it1->second>maxShifts&&(it1->first!=k)){
				return false;
			}
		}
    // check if worker is available thru avail
    if(avail[row][col]==false){
      return false;
    }
    else{
      return true;
    }
}
