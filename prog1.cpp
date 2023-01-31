/**********************************************
	C++ code for project 1 in
	CSE 107 in 2022 winter, UC Santa Cruz,
			for Prof. Chen Qian.
**********************************************/
/*
	Student name:
	UCSC email: ___@ucsc.edu
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

#include "marsaglia-rng.cpp"

using namespace std;

/*
Make a scatter plot of the distribution for these three RNG.
You'll generate num = 10,000 random number in range [0, num).
Make a single scatter plot using matplotlib with the x-axis being 
index of number and the y-axis being the number.

Since it's not easy to plot directly in C++,
You'll need to output your random number to a txt file first,
and then do the scatter plot in Google sheet.
Make sure to label your axis and title your plot appropriately.
*/
void distribution_random(){

}

void distribution_KISS(){

}


void distribution_SHR3(){

}



bool sim_one_game(int n, float p){
    /*
    Write code to simulate one ping pong game to n points
    return the result of win/lose.
    True for win, and False for lose.
    TODO: Your code here
    */
}

float pingpong(int n = 21, float p = 0.3, int ntrials = 5000, int seed = 0){
    /*
    Write code to simulate a ping pong game to n points,
    where the probability of you winning a single point is p.
    You must win by 2; for example, if the score is 21 − 20, 
    the game isn’t over yet. Simulate ntrials # of games.
    :param n: The number of points to play to.
    :param p: The probability of YOU winning a single point.
    :param ntrials: The number of trials to simulate.
    :return: returns the probability YOU win the overall game.
    You can ONLY use the system function rand() to generate randomness.
    You need to generate a random float from the interval [0, 1).

    // TODO: Your code here
    */

}

void plot_output(){
    /*
    Consider the result of diffenrent p in {0, 0.04, 0.08,...,0.96, 1.0}
    and plot a figure with x-axis being p, and the y-axis being the 
    probability of winning the overall game (use your previous function).
    Plot 3 “curves” in different colors, one for each n in {3,11,21}.

    You'll output your probability result to a txt file in this fuction.
    And then do the plot in Google sheet.
    Make sure to label your axis and title your plot appropriately, 
    as well as include a  legend!
    */
    
    // TODO: Your code here
} 


int main()
{
    // You can test out things here. Feel free to write anything below.
    // Example of rng usage:
	/*
    unsigned int i;
    uint32_t k;
    for(i = 0; i< 10; i++){
        k = KISS;
        printf("%"PRIu32"\n", k);
        printf("%d\n", k%100);
    }

    for(i = 0; i< 10; i++){
        k = SHR3;
        printf("%"PRIu32"\n", k);
        printf("%d\n", k%100);
    }
	*/

}
    
