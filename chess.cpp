#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;

int abs(int x)
{
	if(x < 0)
	{
		return -1*x;
	}
	return x;
}

int clearScreen()
{
	cout<<string(100,'\n');
}

class ChessPiece{
	private:
	public:
	string type;
	int player; // 1 or 2
	int x,y; // range from 0 to 7
	bool isNull;
	ChessPiece(string type,int x, int y,int player)
	{
		this->type = type;
		this->x = x;
		this->y = y;
		this->player = player;
		this->isNull = false;
	}
	ChessPiece()
	{
		this->isNull = true;
	}
};

class Move
{
	public:
	int startX,startY,endX,endY;
	Move(int sx,int sy,int ex,int ey)
	{
		this->startX = sx;
		this->startY = sy;
		this->endX = ex;
		this->endY = ey;
	}
};

class ChessBoard
{
	private:
	int currentPlayer;
	vector<ChessPiece> pieces;
	ChessPiece* getPieceAtLocation(int x, int y)
	{
		for(int i=0;i<this->pieces.size();i++)
		{
			ChessPiece *piece = &(this->pieces.at(i));
			if(piece->x == x && piece->y == y)
			{
				return piece;
			}
		}
		return new ChessPiece(); //this constructor denotes a "null" chess piece.
	}
	string validateMove(Move m)
	{
		ChessPiece piece = *getPieceAtLocation(m.startX,m.startY);
		ChessPiece victimPiece = *getPieceAtLocation(m.endX,m.endY);
		
		int x = piece.x;
		int y = piece.y;
		
		if(m.endX == x && m.endY == y){
			return "The chosen Chess Piece must actually move!";
		}
		if(piece.isNull){
			return "The chosen Chess Piece does not exist!";
		}
		if(victimPiece.player == piece.player && !victimPiece.isNull){
			return "You cannot move into your own pieces!";
		}
		
		
		if(piece.type == "king")
		{
			if(abs(x-m.endX) <= 1 && abs(y-m.endY) <= 1)
			{
				return "";
			}
			return "Kings can only move unit away!";
		}
		else if(piece.type == "queen")
		{
			int blockingPieceX = x;
			int blockingPieceY = y;
			if(abs(x-m.endX) == abs(y-m.endY)) // Diagonal
			{
				if(m.endX > x)
				{
					if(m.endY > y) // Right and Up
					{
						int blockingPieceX = x+1;
						int blockingPieceY = y+1;
						while(blockingPieceX != m.endX || blockingPieceY != m.endY)
						{
							if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
							{
								return "There is a piece in the way!";
							}
							blockingPieceX++;
							blockingPieceY++;
						}
						return "";
					}
					else // Right and Down
					{
						int blockingPieceX = x+1;
						int blockingPieceY = y-1;
						while(blockingPieceX != m.endX || blockingPieceY != m.endY)
						{
							if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
							{
								return "There is a piece in the way!";
							}
							blockingPieceX++;
							blockingPieceY--;
						}
						return "";
					}
				}
				else
				{
					if(m.endY > y) // Left and Up
					{
						int blockingPieceX = x-1;
						int blockingPieceY = y+1;
						while(blockingPieceX != m.endX || blockingPieceY != m.endY)
						{
							if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
							{
								return "There is a piece in the way!";
							}
							blockingPieceX--;
							blockingPieceY++;
						}
						return "";
					}
					else // Left and Down
					{
						int blockingPieceX = x-1;
						int blockingPieceY = y-1;
						while(blockingPieceX != m.endX || blockingPieceY != m.endY)
						{
							if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
							{
								return "There is a piece in the way!";
							}
							blockingPieceX--;
							blockingPieceY--;
						}
						return "";
					}
				}
			}
			else if(y-m.endY == 0) // Horizontal
			{
				if(m.endX > x) // Right
				{
					int blockingPieceX = x+1;
					int blockingPieceY = y;
					while(blockingPieceX != m.endX || blockingPieceY != m.endY)
					{
						if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
						{
							return "There is a piece in the way!";
						}
						blockingPieceX++;
					}
					return "";
				}
				else // Left
				{
					int blockingPieceX = x-1;
					int blockingPieceY = y;
					while(blockingPieceX != m.endX || blockingPieceY != m.endY)
					{
						if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
						{
							return "There is a piece in the way!";
						}
						blockingPieceX--;
					}
					return "";
				}
			}
			else if(x-m.endX == 0) // Vertical
			{
				if(m.endY > y) // Up
				{
					int blockingPieceX = x;
					int blockingPieceY = y+1;
					while(blockingPieceX != m.endX || blockingPieceY != m.endY)
					{
						if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
						{
							return "There is a piece in the way!";
						}
						blockingPieceY++;
					}
					return "";
				}
				else // Down
				{
					int blockingPieceX = x;
					int blockingPieceY = y-1;
					while(blockingPieceX != m.endX || blockingPieceY != m.endY)
					{
						if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
						{
							return "There is a piece in the way!";
						}
						blockingPieceY--;
					}
					return "";
				}
			}
			return "A queen cannot move in that way!";
		}
		else if(piece.type == "bishop")
		{
			if(abs(x-m.endX) == abs(y-m.endY)) // Diagonal
			{
				if(m.endX > x)
				{
					if(m.endY > y) // Right and Up
					{
						int blockingPieceX = x+1;
						int blockingPieceY = y+1;
						while(blockingPieceX != m.endX || blockingPieceY != m.endY)
						{
							if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
							{
								return "There is a piece in the way!";
							}
							blockingPieceX++;
							blockingPieceY++;
						}
						return "";
					}
					else // Right and Down
					{
						int blockingPieceX = x+1;
						int blockingPieceY = y-1;
						while(blockingPieceX != m.endX || blockingPieceY != m.endY)
						{
							if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
							{
								return "There is a piece in the way!";
							}
							blockingPieceX++;
							blockingPieceY--;
						}
						return "";
					}
				}
				else
				{
					if(m.endY > y) // Left and Up
					{
						int blockingPieceX = x-1;
						int blockingPieceY = y+1;
						while(blockingPieceX != m.endX || blockingPieceY != m.endY)
						{
							if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
							{
								return "There is a piece in the way!";
							}
							blockingPieceX--;
							blockingPieceY++;
						}
						return "";
					}
					else // Left and Down
					{
						int blockingPieceX = x-1;
						int blockingPieceY = y-1;
						while(blockingPieceX != m.endX || blockingPieceY != m.endY)
						{
							if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
							{
								return "There is a piece in the way!";
							}
							blockingPieceX--;
							blockingPieceY--;
						}
						return "";
					}
				}
			}
			return "A bishop cannot move in that way!";
		}
		else if(piece.type == "knight")
		{
			if((abs(x-m.endX) == 2 && abs(y-m.endY) == 1) || (abs(x-m.endX) == 1 && abs(y-m.endY) == 2))
			{
				return "";
			}
			return "A knight cannot move in that way!";
		}
		else if(piece.type == "rook")
		{
			if(y-m.endY == 0) // Horizontal
			{
				if(m.endX > x) // Right
				{
					int blockingPieceX = x+1;
					int blockingPieceY = y;
					while(blockingPieceX != m.endX || blockingPieceY != m.endY)
					{
						if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
						{
							return "There is a piece in the way!";
						}
						blockingPieceX++;
					}
					return "";
				}
				else // Left
				{
					int blockingPieceX = x-1;
					int blockingPieceY = y;
					while(blockingPieceX != m.endX || blockingPieceY != m.endY)
					{
						if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
						{
							return "There is a piece in the way!";
						}
						blockingPieceX--;
					}
					return "";
				}
			}
			else if(x-m.endX == 0) // Vertical
			{
				if(m.endY > y) // Up
				{
					int blockingPieceX = x;
					int blockingPieceY = y+1;
					while(blockingPieceX != m.endX || blockingPieceY != m.endY)
					{
						if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
						{
							return "There is a piece in the way!";
						}
						blockingPieceY++;
					}
					return "";
				}
				else // Down
				{
					int blockingPieceX = x;
					int blockingPieceY = y-1;
					while(blockingPieceX != m.endX || blockingPieceY != m.endY)
					{
						if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
						{
							return "There is a piece in the way!";
						}
						blockingPieceY--;
					}
					return "";
				}
			}
			return "A rook can only move vertically or horizontally!";
		}
		else if(piece.type == "pawn")
		{
			if(piece.player == 1)
			{
				if(y == 1 && (x-m.endX == 0 && m.endY-y == 2)) //row 2 going 2 spaces forward
				{
					if(victimPiece.isNull && getPieceAtLocation(x,y+1)->isNull)
					{
						return "";
					}
					else
					{
						return "A pawn can only attack diagonally and cannot jump over other pieces!";
					}
				}
				else if(x-m.endX == 0 && m.endY-y == 1) //move 1 forward
				{
					if(victimPiece.isNull)
					{
						return "";
					}
					else
					{
						return "A pawn can only attack diagonally!";
					}
				}
				else if(abs(x-m.endX) == 1 && m.endY-y == 1) //attack
				{
					if(!victimPiece.isNull)
					{
						return "";
					}
					else
					{
						return "A pawn can only move diagonally when attacking!";
					}
				}
				return "Pawns cannot move in that way...ever";
			}
			else if(piece.player == 2)
			{
				if(y == 6 && (x-m.endX == 0 && y-m.endY == 2)) //row 2 going 2 spaces forward
				{
					if(victimPiece.isNull && getPieceAtLocation(x,y-1)->isNull)
					{
						return "";
					}
					else
					{
						return "A pawn can only attack diagonally and cannot jump over other pieces!";
					}
				}
				else if(x-m.endX == 0 && y-m.endY == 1) //move 1 forward
				{
					if(victimPiece.isNull)
					{
						return "";
					}
					else
					{
						return "A pawn can only attack diagonally!";
					}
				}
				else if(abs(x-m.endX) == 1 && y-m.endY == 1) //attack
				{
					if(!victimPiece.isNull)
					{
						return "";
					}
					else
					{
						return "A pawn can only move diagonally when attacking!";
					}
				}
				return "Pawns cannot move in that way...ever";
			}
		}
		else
		{
			return "That type of piece doesn't exist?!";
		}
	}
	public:
	void printBoard()
	{
		for(int y=7;y>=0;y--)
		{
			cout<<endl<<"   ---------------------------------------------------------------------------------"<<endl;
			cout<<setw(2)<<y<<" |";
			for(int x=0;x<=7;x++)
			{
				ChessPiece *piece = getPieceAtLocation(x,y);
				if(!piece->isNull)
				{
					string pieceString = piece->type;
					pieceString.append("_");
					pieceString.append(((piece->player == 1) ? "w" : "b"));
					cout<<setw(9)<<pieceString;
				}
				else
				{
					cout<<setw(9)<<"";
				}
				cout<<"|";
			}
		}
		cout<<endl<<"   ---------------------------------------------------------------------------------"<<endl;
		for(int i=0;i<=7;i++)
		{
			cout<<setw(5)<<"";
			cout<<setw(5)<<i;
		}
		cout<<endl;
	}
	Move getMove()
	{
		int startX,startY,endX,endY;
		Move m = Move(0,0,0,0);
		string message = "";
		do
		{
			clearScreen();
			printBoard();
			cout<<message<<endl;
			string prompt = (currentPlayer == 1) ? "(White) Player One's Turn!" : "(Black) Player Two's Turn!";
			cout<<prompt<<endl;
			cout<<"------------------------"<<endl;
			cout<<"From x-coordinate: "<<endl;
			cin>>startX;
			cout<<"From y-coordinate: "<<endl;
			cin>>startY;
			cout<<"To x-coordinate: "<<endl;
			cin>>endX;
			cout<<"To y-coordinate: "<<endl;
			cin>>endY;
			m = Move(startX,startY,endX,endY);
			message = validateMove(m);

			/*  check that a player does not move into check */
			ChessBoard hypotheticalBoard = ChessBoard(currentPlayer,this->pieces);
			hypotheticalBoard.makeMove(m);
			hypotheticalBoard.check();
			if(hypotheticalBoard.check() == currentPlayer)
			{
				message = "When in check, any move you make must take you out of check!";
			}
			
			// Check that each player only moves his own pieces.
			if(getPieceAtLocation(startX,startY)->player != currentPlayer)
			{
				message = "You cannot move your opponent's pieces!";
			}
		}while(message != "");
		return m;
	}
	bool makeMove(Move m)
	{
		ChessPiece *piece = getPieceAtLocation(m.startX,m.startY);
		for(int i=0;i<pieces.size();i++)
		{
			if(pieces.at(i).x == m.endX && pieces.at(i).y == m.endY)
			{
				pieces.at(i).isNull = true;
			}
		}
		piece->x = m.endX;
		piece->y = m.endY;
		
		this->currentPlayer = (currentPlayer == 1) ? 2 : 1;
	}
	bool stalemate() // returns true if there is a stalemate.
	{
		if(check() == 0)
		{
			for(int i=0;i<pieces.size();i++)
			{
				ChessPiece testPiece = pieces.at(i);
				if(testPiece.player == currentPlayer)
				{
					for(int x = 0;x<=7;x++)
					{
						for(int y = 0;y<=7;y++)
						{
							Move testMove = Move(testPiece.x,testPiece.y,x,y);
							if(validateMove(testMove) == "")
							{
								cout<<"Stalemate: false"<<endl;
								return false;
							}
						}
					}
				}
			}
			cout<<"Stalemate: TRUE!!!"<<endl;
			return true;
		}
	}
	int checkmate() // returns the number of the defeated player (1 or 2) or zero if the game is still going.
	{
		if(check() != 0)
		{
			for(int i=0;i<pieces.size();i++)
			{
				ChessPiece testPiece = pieces.at(i);
				if(testPiece.player == check())
				{
					for(int x = 0;x<=7;x++)
					{
						for(int y = 0;y<=7;y++)
						{
							Move testMove = Move(testPiece.x,testPiece.y,x,y);
							if(validateMove(testMove) == "")
							{
								/*  check that a player does not move into check */
								ChessBoard hypotheticalBoard = ChessBoard(currentPlayer,this->pieces);
								hypotheticalBoard.makeMove(testMove);
								hypotheticalBoard.check();
								if(hypotheticalBoard.check() == 0)
								{
									return 0;				
								}
							}
						}
					}
				}
			}
			return check();
		}
		else
		{
			return 0;
		}
	}
	int check() // returns the number of the player that is in check (1 or 2) or zero if nobody is in check
	{
		ChessPiece whiteKing;
		ChessPiece blackKing;
		for(int i=0;i<pieces.size();i++)
		{
			ChessPiece currentPiece = pieces.at(i);
			if(currentPiece.type == "king" && currentPiece.player == 1)
			{
				whiteKing = currentPiece;
			}
			else if(currentPiece.type == "king" && currentPiece.player == 2)
			{
				blackKing = currentPiece;
			}
		}
		for(int i=0;i<pieces.size();i++)
		{
			ChessPiece currentPiece = pieces.at(i);
			Move attackBlackKing = Move(currentPiece.x,currentPiece.y,blackKing.x,blackKing.y);
			Move attackWhiteKing = Move(currentPiece.x,currentPiece.y,whiteKing.x,whiteKing.y);
			if(currentPiece.player == 1 && validateMove(attackBlackKing) == "")
			{
				return 2;
			}
			else if(currentPiece.player == 2 && validateMove(attackWhiteKing) == "")
			{
				return 1;
			}
		}
		return 0;
	}
	ChessBoard()
	{
		this->currentPlayer = 1;
		this->pieces = vector<ChessPiece>();
		for(int x=0;x<=7;x++)
		{
			this->pieces.push_back(ChessPiece("pawn",x,1,1));
			this->pieces.push_back(ChessPiece("pawn",x,6,2));
		}
	
		// Player 1 Pieces
		this->pieces.push_back(ChessPiece("king",4,0,1));
		this->pieces.push_back(ChessPiece("queen",3,0,1));
		this->pieces.push_back(ChessPiece("bishop",2,0,1));
		this->pieces.push_back(ChessPiece("bishop",5,0,1));
		this->pieces.push_back(ChessPiece("knight",1,0,1));
		this->pieces.push_back(ChessPiece("knight",6,0,1));
		this->pieces.push_back(ChessPiece("rook",0,0,1));
		this->pieces.push_back(ChessPiece("rook",7,0,1));
		
		// Player 2 Pieces
		this->pieces.push_back(ChessPiece("king",4,7,2));
		this->pieces.push_back(ChessPiece("queen",3,7,2));
		this->pieces.push_back(ChessPiece("bishop",2,7,2));
		this->pieces.push_back(ChessPiece("bishop",5,7,2));
		this->pieces.push_back(ChessPiece("knight",1,7,2));
		this->pieces.push_back(ChessPiece("knight",6,7,2));
		this->pieces.push_back(ChessPiece("rook",0,7,2));
		this->pieces.push_back(ChessPiece("rook",7,7,2));		
	}
	ChessBoard(int currentPlayer, vector<ChessPiece> otherPieces)
	{
		this->currentPlayer = currentPlayer;
		this->pieces = vector<ChessPiece>(otherPieces);
	}
};


int main()
{
	ChessBoard cb = ChessBoard();
	bool continuePlaying = true;
	int checkmateStatus = 0;
	bool stalemateStatus = false;
	while(continuePlaying)
	{
		Move m = cb.getMove();
		cb.makeMove(m);
		checkmateStatus = cb.checkmate();
		stalemateStatus = cb.stalemate();
		if(checkmateStatus != 0 || stalemateStatus == true)
		{
			continuePlaying = false;
		}
	}
	if(checkmateStatus != 0)
	{
		cout<<"Checkmate!"<<endl;
		if(checkmateStatus == 1)
		{
			cout<<"Black (player 2) Wins!"<<endl;
		}
		else
		{
			cout<<"White (player 1) Wins!"<<endl;
		}
	}
	else if(stalemateStatus == true)
	{
		cout<<"Stalemate!"<<endl;
	}
	else{
		cout<<"game unexpectedly ended"<<endl;
	}
	return 0;
}


