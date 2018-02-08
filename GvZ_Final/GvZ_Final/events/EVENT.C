/* ================================================
- Module Name: event
- Purpose: handles all events in the game
================================================ */
#include "EVENT.H"
/* ================================================
- Name: move
- Purpose: handles all the movement calls at once
================================================ */
void move(struct Model *gamePtr)
{
	moveZombie(gamePtr);
	moveBullet(gamePtr);
	movePlayer(gamePtr);
	/*print board values*/
}
/* ================================================
- Name: movePlayer
- Purpose: handles the movement for players
================================================ */
void movePlayer(struct Model *gamePtr)
{
	bool Collision = FALSE;
	bool found = FALSE;
	int i, newCor;
	for(i = 0; i < NUMWALLS && !Collision; i++)
	{
		switch(gamePtr->players[0].XDirection)
		{
			case 1:
			newCor = gamePtr->players[0].Xpos + gamePtr->players[0].Speed;
			break;
			case -1:
			newCor = gamePtr->players[0].Xpos - gamePtr->players[0].Speed;
		}
		switch(gamePtr->players[0].YDirection)
		{
			case 1:
			newCor = gamePtr->players[0].Ypos + gamePtr->players[0].Speed;
			break;
			case -1:
			newCor = gamePtr->players[0].Ypos - gamePtr->players[0].Speed;
		}
		if(gamePtr->players[0].XDirection != 0)
		{
			if(newCor < gamePtr->walls[i].Xpos2 && 
			newCor + gamePtr->players[0].Width >= gamePtr->walls[i].Xpos1 - 5 &&
			gamePtr->players[0].Ypos < gamePtr->walls[i].Ypos2 &&
			gamePtr->players[0].Ypos + gamePtr->players[0].Height > gamePtr->walls[i].Ypos1)
			{
				Collision = TRUE;
				if(gamePtr->players[0].XDirection == 1)
					gamePtr->players[0].Xpos = gamePtr->walls[i].Xpos1 - gamePtr->players[0].Width - 5;
				else
					gamePtr->players[0].Xpos = gamePtr->walls[i].Xpos2 + 1;
			}
		}
		else
		{
			if(gamePtr->players[0].Xpos < gamePtr->walls[i].Xpos2 && 
			gamePtr->players[0].Xpos + gamePtr->players[0].Width > gamePtr->walls[i].Xpos1 &&
			newCor < gamePtr->walls[i].Ypos2 &&
			newCor + gamePtr->players[0].Height > gamePtr->walls[i].Ypos1)
			{
				Collision = TRUE;
				if(gamePtr->players[0].YDirection == 1)
					gamePtr->players[0].Ypos = gamePtr->walls[i].Ypos1 - gamePtr->players[0].Height;
				else
					gamePtr->players[0].Ypos = gamePtr->walls[i].Ypos2 + 1;
			}
		}
	}
	if(!Collision)
	{	
		for(i = 0; i < NUMPOINT && !found; i++)
		{
			if(gamePtr->point[i].Active)
			{
				found = TRUE;
				if(gamePtr->players[0].Xpos < gamePtr->point[i].Xpos2 && 
				gamePtr->players[0].Xpos + gamePtr->players[0].Width > gamePtr->point[i].Xpos &&
				gamePtr->players[0].Ypos < gamePtr->point[i].Ypos2 &&
				gamePtr->players[0].Ypos + gamePtr->players[0].Height > gamePtr->point[i].Ypos)
				{
					gamePtr->Score += 5;
					gamePtr->point[i].Active = FALSE;
					gamePtr->point[i].Clear = TRUE;
					setPoint(gamePtr, i);
				}
			}
		}
		if(gamePtr->players[0].XDirection != 0)
		{
			gamePtr->players[0].Xold = gamePtr->players[0].Xpos;
			gamePtr->players[0].Xpos = newCor;
		}
		else
		{
			gamePtr->players[0].Yold = gamePtr->players[0].Ypos;
			gamePtr->players[0].Ypos = newCor;
		}
	}
}
/* ================================================
- Name: moveBullet
- Purpose: handles the movement for bullets
================================================ */
void moveBullet(struct Model *gamePtr)
{
	bool Collision = FALSE;
	int i,j, newCor;
	for(j = 0; j < NUMBULLET && !Collision; j++)
	{
		if(gamePtr->bullets[j].Active)
		{
			switch(gamePtr->bullets[j].XDirection)
			{
				case 1:
				newCor = gamePtr->bullets[j].Xpos + gamePtr->bullets[j].Speed;
				break;
				case -1:
				newCor = gamePtr->bullets[j].Xpos - gamePtr->bullets[j].Speed;
			}
			switch(gamePtr->bullets[j].YDirection)
			{
				case 1:
				newCor = gamePtr->bullets[j].Ypos + gamePtr->bullets[j].Speed;
				break;
				case -1:
				newCor = gamePtr->bullets[j].Ypos - gamePtr->bullets[j].Speed;
			}
			for(i = 0; i < NUMWALLS && !Collision; i++)
			{
				if(gamePtr->bullets[j].XDirection != 0)
				{
					if(newCor < gamePtr->walls[i].Xpos2 && 
					newCor + gamePtr->bullets[j].Width > gamePtr->walls[i].Xpos1 - 5 &&
					gamePtr->bullets[j].Ypos < gamePtr->walls[i].Ypos2 &&
					gamePtr->bullets[j].Ypos + gamePtr->bullets[j].Height > gamePtr->walls[i].Ypos1)
					{
						Collision = TRUE;
						gamePtr->bullets[j].Active = FALSE;
						gamePtr->bullets[j].Clear = TRUE;
					}
				}
				else
				{
					if(gamePtr->bullets[j].Xpos < gamePtr->walls[i].Xpos2 && 
					gamePtr->bullets[j].Xpos + gamePtr->bullets[j].Width > gamePtr->walls[i].Xpos1 &&
					newCor < gamePtr->walls[i].Ypos2 &&
					newCor + gamePtr->bullets[j].Height > gamePtr->walls[i].Ypos1)
					{
						Collision = TRUE;
						gamePtr->bullets[j].Active = FALSE;
						gamePtr->bullets[j].Clear = TRUE;
					}
				}
			}
			if(!Collision)
			{
				for(i = 0; i < NUMZOMBIE && !Collision; i++)
				{
					if(gamePtr->zombies[i].Active)
					{
						if(gamePtr->bullets[j].XDirection != 0)
						{
							if(newCor < gamePtr->zombies[i].Xpos + gamePtr->zombies[i].Width && 
							newCor + gamePtr->bullets[j].Width > gamePtr->zombies[i].Xpos &&
							gamePtr->bullets[j].Ypos < gamePtr->zombies[i].Ypos + gamePtr->zombies[i].Height &&
							gamePtr->bullets[j].Ypos + gamePtr->bullets[j].Height > gamePtr->zombies[i].Ypos)
							{
								Collision = TRUE;
								gamePtr->bullets[j].Active = FALSE;
								gamePtr->bullets[j].Clear = TRUE;
								gamePtr->zombies[i].Active = FALSE;
								gamePtr->zombies[i].Clear = TRUE;
							}
						}
						else
						{
							if(gamePtr->bullets[j].Xpos < gamePtr->zombies[i].Xpos + gamePtr->zombies[i].Width && 
							gamePtr->bullets[j].Xpos + gamePtr->bullets[j].Width > gamePtr->zombies[i].Xpos &&
							newCor < gamePtr->zombies[i].Ypos + gamePtr->zombies[i].Height &&
							newCor + gamePtr->bullets[j].Height > gamePtr->zombies[i].Ypos)
							{
								Collision = TRUE;
								gamePtr->bullets[j].Active = FALSE;
								gamePtr->bullets[j].Clear = TRUE;
								gamePtr->zombies[i].Active = FALSE;
								gamePtr->zombies[i].Clear = TRUE;
								gamePtr->Score++;
							}
						}
					}
				}
			}
			if(!Collision)
			{
				if(gamePtr->bullets[j].XDirection != 0)
				{
					gamePtr->bullets[j].Xold = gamePtr->bullets[j].Xpos;
					gamePtr->bullets[j].Xpos = newCor;
				}
				else
				{
					gamePtr->bullets[j].Yold = gamePtr->bullets[j].Ypos;
					gamePtr->bullets[j].Ypos = newCor;
				}
			}
		}
	}
}
/* ================================================
- Name: moveZombie
- Purpose: handles the movement for zombies
================================================ */
void moveZombie(struct Model *gamePtr)
{
	bool Collision = FALSE;
	int i,j, newCor;
	
	for(j = 0; j < NUMZOMBIE && !Collision; j++)
	{
		if(gamePtr->zombies[j].Active)
		{
			switch(gamePtr->zombies[j].XDirection)
			{
				case 1:
				newCor = gamePtr->zombies[j].Xpos + gamePtr->zombies[j].Speed;
				break;
				case -1:
				newCor = gamePtr->zombies[j].Xpos - gamePtr->zombies[j].Speed;
			}
			switch(gamePtr->zombies[j].YDirection)
			{
				case 1:
				newCor = gamePtr->zombies[j].Ypos + gamePtr->zombies[j].Speed;
				break;
				case -1:
				newCor = gamePtr->zombies[j].Ypos - gamePtr->zombies[j].Speed;
			}
			for(i = 0; i < NUMWALLS && !Collision; i++)
			{
				if(gamePtr->zombies[j].XDirection != 0)
				{
					if(newCor < gamePtr->walls[i].Xpos2 && 
					newCor + gamePtr->zombies[j].Width > gamePtr->walls[i].Xpos1 &&
					gamePtr->zombies[j].Ypos < gamePtr->walls[i].Ypos2 &&
					gamePtr->zombies[j].Ypos + gamePtr->zombies[j].Height > gamePtr->walls[i].Ypos1)
					{
						Collision = TRUE;
						if(gamePtr->zombies[j].XDirection == 1)
							gamePtr->zombies[j].Xpos = gamePtr->walls[i].Xpos1 - gamePtr->zombies[j].Width;
						else
							gamePtr->zombies[j].Xpos = gamePtr->walls[i].Xpos2 + 1;
					}
				}
				else
				{
					if(gamePtr->zombies[j].Xpos < gamePtr->walls[i].Xpos2 && 
					gamePtr->zombies[j].Xpos + gamePtr->zombies[j].Width > gamePtr->walls[i].Xpos1 &&
					newCor < gamePtr->walls[i].Ypos2 &&
					newCor + gamePtr->zombies[j].Height > gamePtr->walls[i].Ypos1)
					{
						Collision = TRUE;
						if(gamePtr->zombies[j].YDirection == 1)
							gamePtr->zombies[j].Ypos = gamePtr->walls[i].Ypos1 - gamePtr->zombies[j].Height;
						else
							gamePtr->zombies[j].Ypos = gamePtr->walls[i].Ypos2 + 1;
					}
				}
			}
			if(!Collision)
			{
				for(i = 0; i < NUMPLAYER && !Collision; i++)
				{
					if(gamePtr->zombies[j].XDirection != 0)
					{
						if(newCor < gamePtr->players[i].Xpos - 15 + gamePtr->players[i].Width && 
						newCor + gamePtr->zombies[j].Width > gamePtr->players[i].Xpos + 15 &&
						gamePtr->zombies[j].Ypos < gamePtr->players[i].Ypos - 3 + gamePtr->players[i].Height &&
						gamePtr->zombies[j].Ypos + gamePtr->zombies[j].Height > gamePtr->players[i].Ypos + 3)
						{
							Collision = TRUE;
							gamePtr->Restart = TRUE;
							gamePtr->Lives--;
						}
					}
					else
					{
						if(gamePtr->zombies[j].Xpos < gamePtr->players[i].Xpos - 15 + gamePtr->players[i].Width && 
						gamePtr->zombies[j].Xpos + gamePtr->zombies[j].Width > gamePtr->players[i].Xpos  + 15 &&
						newCor < gamePtr->players[i].Ypos -3 + gamePtr->players[i].Height &&
						newCor + gamePtr->zombies[j].Height > gamePtr->players[i].Ypos + 3)
						{
							Collision = TRUE;
							gamePtr->Restart = TRUE;
							gamePtr->Lives--;
						}
					}
				}
			}
			if(!Collision)
			{
				for(i = 0; i < NUMZOMBIE && !Collision; i++)
				{
					if(gamePtr->zombies[i].Active)
					{
						if(j != i)
						{
							if(gamePtr->zombies[j].XDirection != 0)
							{
								if(newCor < gamePtr->zombies[i].Xpos + gamePtr->zombies[i].Width && 
								newCor + gamePtr->zombies[j].Width > gamePtr->zombies[i].Xpos &&
								gamePtr->zombies[j].Ypos < gamePtr->zombies[i].Ypos + gamePtr->zombies[i].Height &&
								gamePtr->zombies[j].Ypos + gamePtr->zombies[j].Height > gamePtr->zombies[i].Ypos)
								{
									if(j > i )
									{
										Collision = TRUE;
										gamePtr->zombies[j].Xold = gamePtr->zombies[j].Xpos;
										gamePtr->zombies[j].Xpos = newCor;
									}
								}
							}
							else
							{
								if(gamePtr->zombies[j].Xpos < gamePtr->zombies[i].Xpos + gamePtr->zombies[i].Width && 
								gamePtr->zombies[j].Xpos + gamePtr->zombies[j].Width > gamePtr->zombies[i].Xpos &&
								newCor < gamePtr->zombies[i].Ypos + gamePtr->zombies[i].Height &&
								newCor + gamePtr->zombies[j].Height > gamePtr->zombies[i].Ypos)
								{
									if(j > i )
									{
										Collision = TRUE;
										gamePtr->zombies[j].Yold = gamePtr->zombies[j].Ypos;
										gamePtr->zombies[j].Ypos = newCor;
									}
								}	
							}
						}
					}
				}
			}
			if(!Collision)
			{
				if(gamePtr->zombies[j].XDirection != 0)
				{
					gamePtr->zombies[j].Xold = gamePtr->zombies[j].Xpos;
					gamePtr->zombies[j].Xpos = newCor;
				}
				else
				{
					gamePtr->zombies[j].Yold = gamePtr->zombies[j].Ypos;
					gamePtr->zombies[j].Ypos = newCor;
				}
			}
		}
	}
}

