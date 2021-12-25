



#include "bots.h"

#include "stdlib.h"





void cDijkstra::Build(cBotBase& bot)

{ //initializing arrays

//task B

    for (int i = 0; i < GRIDWIDTH; i++)

    {

        for (int j = 0; j < GRIDWIDTH; j++)

        {

            closed[i][j] = false;// all nodes are set to open

            cost[i][j] = 1000000.0;// nodes iniatilized to a big number

            linkX[i][j] = -1;

            linkY[i][j] = -1;

            inPath[i][j] = false;// every path iniatilized to false.





        }

    }



    // cost set to zero, as path is yet to start.

    //bot.PositionX refers to coordinate position of X

    //bot.PositionY refers to coordinate position of Y

    cost[bot.PositionX()][bot.PositionY()] = 0;

    int costforX = 0;// cost of X

    int costforY = 0;// cost of Y



    //Repeatable while loop being executed to find open nodes with lowest cost, that are not blocked from the map layout

    while (closed[gTarget.PositionX()][gTarget.PositionY()] == false)

    {



        float currentCost = 1000000.0f;





        //current cost  gets updated whilst the pathway is being generated.

        //as the pathway moves along the cheapest costs would be added to the existing costs.



        //closed[bot.PositionX()][bot.PositionY()] = true; //set to close





        for (int i = 0; i < GRIDWIDTH; i++)

        {

            for (int j = 0; j < GRIDHEIGHT; j++)

            {

                if ((cost[i][j] < currentCost) && (!closed[i][j]) && (gLevel.isValid(i, j)))

                    // if new cost after moving pathway is equal or cheaper than current cost, update and close node.

                {

                    currentCost = cost[i][j];

                    costforX = i;

                    costforY = j;

                }

            }



        }

        //set the location to closed. (task b/ part 2)

        closed[costforX][costforY] = true;





        //for loop with if conditons that defines costs for 8 locations surrounding the current node.

        //Top, left,right and bottom nodes costing 1

        // Diagonal nodes such as top left, top right and bottom left, bottom right costing 1.4



            //right

        if ((gLevel.isValid(costforX + 1, costforY)) && !closed[costforX + 1][costforY] && ((cost[costforX][costforY] + 1) < (cost[costforX + 1][costforY])))



        {







            cost[costforX + 1][costforY] = cost[costforX][costforY] + 1;



            linkX[costforX + 1][costforY] = costforX;



            linkY[costforX + 1][costforY] = costforY;



        }

        //left

        if ((gLevel.isValid(costforX - 1, costforY)) && !closed[costforX - 1][costforY] && ((cost[costforX][costforY] + 1) < (cost[costforX - 1][costforY])))



        {







            cost[costforX - 1][costforY] = cost[costforX][costforY] + 1;



            linkX[costforX - 1][costforY] = costforX;



            linkY[costforX - 1][costforY] = costforY;



        }

        //up

        if ((gLevel.isValid(costforX, costforY + 1)) && !closed[costforX][costforY + 1] && ((cost[costforX][costforY] + 1) < (cost[costforX][costforY + 1])))



        {







            cost[costforX][costforY + 1] = cost[costforX][costforY] + 1;



            linkX[costforX][costforY + 1] = costforX;



            linkY[costforX][costforY + 1] = costforY;



        }

        //down

        if ((gLevel.isValid(costforX, costforY - 1)) && !closed[costforX][costforY - 1] && ((cost[costforX][costforY] + 1) < (cost[costforX][costforY - 1])))



        {







            cost[costforX][costforY - 1] = cost[costforX][costforY] + 1;



            linkX[costforX][costforY - 1] = costforX;



            linkY[costforX][costforY - 1] = costforY;



        }

        //top right

        if ((gLevel.isValid(costforX + 1, costforY + 1)) && !closed[costforX + 1][costforY + 1] && ((cost[costforX][costforY] + 1.4) < (cost[costforX + 1][costforY + 1])))



        {







            cost[costforX + 1][costforY + 1] = cost[costforX][costforY] + 1.4;



            linkX[costforX + 1][costforY + 1] = costforX;



            linkY[costforX + 1][costforY + 1] = costforY;



        }// top left

        if ((gLevel.isValid(costforX - 1, costforY + 1)) && !closed[costforX - 1][costforY + 1] && ((cost[costforX][costforY] + 1.4) < (cost[costforX - 1][costforY + 1])))



        {







            cost[costforX - 1][costforY + 1] = cost[costforX][costforY] + 1.4;



            linkX[costforX - 1][costforY + 1] = costforX;



            linkY[costforX - 1][costforY + 1] = costforY;



        }

        //bottom left

        if ((gLevel.isValid(costforX - 1, costforY - 1)) && !closed[costforX - 1][costforY - 1] && ((cost[costforX][costforY] + 1.4) < (cost[costforX - 1][costforY - 1])))



        {







            cost[costforX - 1][costforY - 1] = cost[costforX][costforY] + 1.4;



            linkX[costforX - 1][costforY - 1] = costforX;



            linkY[costforX - 1][costforY - 1] = costforY;



        }

        //bottom right

        if ((gLevel.isValid(costforX + 1, costforY - 1)) && !closed[costforX + 1][costforY - 1] && ((cost[costforX][costforY] + 1.4) < (cost[costforX + 1][costforY - 1])))



        {







            cost[costforX + 1][costforY - 1] = cost[costforX][costforY] + 1.4;



            linkX[costforX + 1][costforY - 1] = costforX;



            linkY[costforX + 1][costforY - 1] = costforY;



        }



    }











    //Once loop terminates, locations are extracted from path that has been defined through linkX and Link y arrays.

    bool done = false;

    //set to true when we are back at the bot's position

    int nextClosedX = gTarget.PositionX(); //start of path

    int nextClosedY = gTarget.PositionY(); //start of path

    while (!done)

    {//inPath array set to true, once corresponding path entries and denoted.

        inPath[nextClosedX][nextClosedY] = true; //sets location closed

        int tmpX = nextClosedX;

        int tmpY = nextClosedY;

        nextClosedX = linkX[tmpX][tmpY];

        nextClosedY = linkY[tmpX][tmpY];

        if ((nextClosedX == bot.PositionX()) && (nextClosedY ==

            bot.PositionY())) done = true;// class variable to true

    }

    completed = true;





}



cDijkstra gDijkstra;
void cAStar::Build(cBotBase& bot)

{ //initializing arrays

//task B

    for (int i = 0; i < GRIDWIDTH; i++)

    {

        for (int j = 0; j < GRIDWIDTH; j++)

        {

            closed[i][j] = false;// all nodes are set to open

            cost[i][j] = 1000000.0;// nodes iniatilized to a big number

            linkX[i][j] = -1;

            linkY[i][j] = -1;

            inPath[i][j] = false;// every path iniatilized to false.





        }

    }

}