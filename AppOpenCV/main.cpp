/* 
 * File:   main.cpp
 * Author: ainoa
 *
 * Created on April 9, 2015, 11:11 AM
 */

#include <cstdlib>  //for the random values
#include <ctime>
#include <iostream>
#include <cv.h>

//     |1|5|-|
//   |2|3|  |6|
//      |    |
//   |0|4|---|

using namespace std;
using namespace cv;

const int size = 7;
const double Gamma = 0.8;
int initialStates[size] = {0, 1, 2, 3, 4, 5, 6};
int iterations = 5; 
int currentState;

Mat R = (Mat_<int>(7,7) << -1, -1, -1, -1, 0, -1, -1, -1, -1, -1, 0, -1, 0, -1,
            -1, -1, -1, 0, -1, -1, -1, -1, 0, 0, -1, 0, -1, -1, 0, -1, -1, 0, -1, -1, 100,
            -1, 0, -1, -1, -1, -1, 100, -1, -1, -1, -1, 0, 0, 100); 
//cout<< "Matrix R:"<<endl<< " " << R << endl << endl;

Mat Q = Mat_<int>(Mat::zeros(7,7, CV_8U));

//cout<< "Matrix Q:"<<endl<< " " << Q << endl << endl;

void episode(int initialStates);
void selectAction();
int getRandomValue();
int maxQValue(int state, bool returnIndexOnly);
int formula(int action);


int main() {
  
    int newState;

    //Starting at all initial states
    for(int i = 0; i < iterations; i++)
    {
        for(int j = 0; j < size; j++)
        {
            episode(initialStates[j]);
	}
    }
    
    //Print Q matrix
    cout<< "Matrix Q:"<<endl<< " " << Q << endl << endl;
     
    //Print sequences of states
    cout<< "Sequences of states:"<<endl;
    for(int i = 0; i < size; i++)
    {
        currentState = initialStates[i];
        newState = 0;
        while(currentState < 6)
        {
            newState = maxQValue(currentState, true);
            cout << currentState << ", ";
            currentState = newState;
        }
        cout << "6" << endl;
    }
}

void episode(int initialStates)  //The agent will explore from state to state until it reaches the goal
{
    currentState = initialStates;
    
    while(currentState != 6)
    {
        selectAction();
    }
    
    for(int i = 0; i < size; i++)
    {
        selectAction();
    }
}


void selectAction()
{
    int possibleAction;
    
    possibleAction = getRandomValue();
    if(R.at<int>(currentState,possibleAction) >= 0)
    {
        Q.at<int>(currentState,possibleAction) = formula(possibleAction);
        currentState = possibleAction;
    }
    
}


int getRandomValue()
{
    int randNumAction;
    bool valid = false;
    
    do
    {        
        randNumAction = rand() % 7;
        if(R.at<int>(currentState,randNumAction) >= 0)
        {
            valid = true;
        }
    }while(valid == false);
    
    return randNumAction;
}

int maxQValue(int state, bool returnIndexOnly)
{
// if returnIndexOnly = true, a Q matrix index is returned.
// if returnIndexOnly = false, a Q matrix element is returned.
    
    int winner = 0;
    bool foundNewWinner = false;
    bool done = false;
    
    if(done == false)
    {    
        for(int i = 0; i < size; i++)
        {
            if((i < winner) || (i > winner))
            {
		if(Q.at<int>(state,i) > Q.at<int>(state,winner))
                {
                    winner = i;
                    foundNewWinner = true;
                }
            }
	}

	if(foundNewWinner == false)
        {
            done = true;
	}

    }

    if(returnIndexOnly == true)
    {
	return winner;
    }
    
    else
    {
	return Q.at<int>(state,winner);
    }
    
}

int formula(int action)
{
//  Q(state, action) = R(state, action) + Gamma * Max[Q(next state, all actions)]
    
    return (R.at<int>(currentState,action) + (Gamma * maxQValue(action, false)));
}

