#include<iostream>
#include <cstdlib>
#include<unistd.h>
using namespace std;
void instructions(){
	 cout<<endl<<endl<<"\t\t\t\t\t\t\t\t          RULES TO PLAY"<<endl<<endl<<endl;
            cout<<"\t\t\t\t\t\t         =============================================="<<endl<<endl<<endl;
            cout<<"\t\t\t\t\t\t         ______________________________________________ "<<endl;
            cout<<"\t\t\t\t\t\t          ||    WP:White Pawn   |  BP=Black pawn    ||"<<endl;
            cout<<"\t\t\t\t\t\t          ||    WN=White Knight |  BN=Black Knight  ||"<<endl;
            cout<<"\t\t\t\t\t\t          ||    WB=White Bishop |  BB=Black Bishop  ||"<<endl;
            cout<<"\t\t\t\t\t\t          ||    WR=White Rook   |  BR=Black Rook    ||"<<endl;
            cout<<"\t\t\t\t\t\t          ||    WK=White King   |  BK=Black King    ||"<<endl;
            cout<<"\t\t\t\t\t\t          ||                                        ||"<<endl;
            cout<<"\t\t\t\t\t\t         ______________________________________________ "<<endl;
            cout<<"\t\t\t\t\t\t         ++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
            cout<<"\t\t\t\t\t\t                          ROW TO COLUMN"<<endl;
            cout<<"\t\t\t\t\t\t                          W=WHITE PIECE"<<endl;
            cout<<"\t\t\t\t\t\t                          B=BLACK PIECE"<<endl;
            cout<<"\t\t\t\t\t\t         ++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
}
class Game{
	private:
        //virtual bool SquaresCorrect(int FromRow, int FromCol, int ToRow, int ToCol, Game* GameBoard[8][8]) = 0;
        char PlayerPieceColor;
    public:
        Game(char PieceColor) : PlayerPieceColor(PieceColor) {}
        char GetColor() {
            return PlayerPieceColor;
		}
        virtual char GetPiece() = 0;
        virtual bool SquaresCorrect(int FromRow, int FromCol, int ToRow, int ToCol, Game* GameBoard[8][8]) = 0;
        bool IsMoveCorrect(int FromRow, int FromCol, int ToRow, int ToCol, Game* GameBoard[8][8]) {
            Game* uDest;
			uDest= GameBoard[ToRow][ToCol];
            if ((uDest == 0) || (PlayerPieceColor != uDest->GetColor())) {
                return SquaresCorrect(FromRow, FromCol, ToRow, ToCol, GameBoard);}
            else{
            	return false;
			}
		}
	//destructor
    ~Game() {}
};
//***King can move in its line or rwo***
class king:public Game{
	public:
		//parameterized constructor
		king(char PieceColor):Game(PieceColor){}
		//virtual function
		virtual char GetPiece(){
			return 'K';
		}
		bool SquaresCorrect(int FromRow,int FromCol,int ToRow,int ToCol,Game*GameBoard[8][8]){
			//locations that king can move
		     int deltaRow=FromRow-ToRow;
		     int deltaColumn=FromCol-ToCol;
		     if((deltaRow>=-1) &&(deltaRow<=1) && (deltaColumn>=-1) && (deltaColumn<=1)){
		     	return true; 
			 }
			 else{
			 	return false;
			 }
		    
		}
		//destructor
		~king(){}
};
//***Queen can move in any direction***
class Queen:public Game{
	public:
		Queen(char PieceColor):Game(PieceColor){}
		virtual char GetPiece() {
        return 'Q';}
    	bool SquaresCorrect(int FromRow,int FromCol,int ToRow,int ToCol,Game*GameBoard[8][8]){
    		if (FromRow == ToRow || FromCol == ToCol) {
            int BlankRow = (ToRow - FromRow > 0) ? 1 : -1;
            if((ToRow-FromRow)>0){
					BlankRow=1;}
			else{
				BlankRow=-1;}
            int BlankCol;
            if((ToCol-FromCol)>0){
					BlankCol=1;}
			else{
				BlankCol=-1;}
           int CheckRow = FromRow + BlankRow;
           int CheckCol = FromCol + BlankCol;
           if (FromRow == ToRow) {
           while (CheckCol != ToCol) {
                if (GameBoard[FromRow][CheckCol] != 0) {
                    return false;
                }
                 CheckCol += BlankCol;}
			}
		    else {
                while (CheckRow != ToRow) {
                    if (GameBoard[CheckRow][FromCol] != 0) {
                    return false;}
                    CheckRow += BlankRow;
				}
			}
            return true;
    }
    else if((ToCol-FromCol==ToRow-FromRow) || (ToCol-FromCol==FromRow-ToRow)){
    	//making use of ternary operator
		int BlankRow = (ToRow - FromRow > 0) ? 1 : -1;
        int BlankCol = (ToCol - FromCol > 0) ? 1 : -1;
        int CheckRow = FromRow + BlankRow;
        int CheckCol = FromCol + BlankCol;
        while (CheckRow != ToRow) {
            if (GameBoard[CheckRow][CheckCol] != 0) {
                return false;
            }
            CheckRow += BlankRow;
            CheckCol += BlankCol;
        }

        return true;
    }
    return false;

	}
	//destructor
	~Queen(){}
    
};
//***Pawn can move one square straight ahead***
class Pawn : public Game{
    public:
        Pawn(char PieceColor) : Game(PieceColor) {}
        virtual char GetPiece() {
            return 'P';}
        bool SquaresCorrect(int FromRow, int FromCol, int ToRow, int ToCol, Game* GameBoard[8][8]) {
            Game* uDest ;
			uDest=GameBoard[ToRow][ToCol];
            if (uDest == 0){
            // Where squares are unoccupied
            if (FromCol == ToCol) {
                if (GetColor() == 'W') {
                    if(ToRow == FromRow + 1) {
                        return true;
                    }
                } 
				else{
                    if (ToRow == FromRow - 1) {
                        return true;
                    }
                }
            }
        } 
		else{
            // Dest holds piece of opposite color
            if ((FromCol == ToCol + 1) || (FromCol == ToCol - 1)) {
                if (GetColor() == 'W') {
                    if (ToRow == FromRow + 1) {
                        return true;
                    }
                } 
				else {
                    if (ToRow == FromRow - 1) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    //destructor
    ~Pawn() {}
};

//***Knight jumps in making the shortest move***
class Knight : public Game{
    public:
        Knight(char PieceColor) : Game(PieceColor) {}
        virtual char GetPiece() {
            return 'N';}
        bool SquaresCorrect(int FromRow, int FromCol, int ToRow, int ToCol, Game* GameBoard[8][8]) {
        // Destination square is unoccupied or occupied by opposite color
            if ((FromCol == ToCol + 1) || (FromCol == ToCol - 1)) {
                if ((FromRow == ToRow + 2) || (FromRow == ToRow - 2)) {
                    return true;}
			}
            if ((FromCol == ToCol + 2) || (FromCol == ToCol - 2)) {
                if ((FromRow == ToRow + 1) || (FromRow == ToRow - 1)) {
                    return true;}
			}
            return false;
		}
     ~Knight() {}
};

//***Bishop moves diagonally***
class Bishop:public Game{
	public:
		//Parameterized Constructor
		Bishop(char PieceColor):Game(PieceColor){}
		
		virtual char GetPiece(){
			return 'B';
		}
		bool SquaresCorrect(int FromRow,int FromCol,int ToRow,int ToCol,Game*GameBoard[8][8]){
			if((ToCol-FromCol==ToRow-FromRow) || (ToCol-FromCol==FromRow-ToRow)){
				int BlankRow;
				if((ToRow-FromRow)>0){
					BlankRow=1;	}
				else{
					BlankRow=-1;	}
                int BlankCol;
                if((ToCol-FromCol)>0){
					BlankCol=1;	}
				else{
					BlankCol=-1;	}
                int CheckRow = FromRow + BlankRow;
                int CheckCol = FromCol + BlankCol;
                while (CheckRow != ToRow) {
                    if (GameBoard[CheckRow][CheckCol] != 0) {
                        return false;
					}
                    CheckRow += BlankRow;
                    CheckCol += BlankCol;
				}
                return true;
			}
            return false;
		}
	//destructor
	~Bishop(){}
};

//***Rook can move in its line or row***
class Rook:public Game{
	public:
		//parameterized constructor
		Rook(char PieceColor):Game(PieceColor){}
			virtual char GetPiece(){	return 'R';	}
		bool SquaresCorrect(int FromRow,int FromCol,int ToRow,int ToCol,Game*GameBoard[8][8]){
			if (FromRow == ToRow || FromCol == ToCol) {
                int BlankRow;
                if((ToRow-FromRow)>0){
					BlankRow=1;	}
				else{
					BlankRow=-1;	}
                int BlankCol;
                if((ToCol-FromCol)>0){
					BlankCol=1;	}
				else{
					BlankCol=-1;	}
                int CheckRow = FromRow + BlankRow;
                int CheckCol = FromCol + BlankCol;
                if (FromRow == ToRow) {
                while (CheckCol != ToCol) {
                    if (GameBoard[FromRow][CheckCol] != 0) {
                        return false;	}
                 CheckCol += BlankCol;
				}	}
		    else{
             while (CheckRow != ToRow) {
                if (GameBoard[CheckRow][FromCol] != 0) {
                    return false;    }
                 CheckRow += BlankRow;
            } }
        return true; }
    return false;	}
	//destructor
	~Rook(){}
};

class CBoard{
	public:
		Game*GameBoard[8][8];
		CBoard(){
			//Allocate Black Pieces
			//Initialize each cell of the chess board[8x8] to 0
			for(int row=0; row<8;++row){
				for(int column=0; column<8;++column){
				GameBoard[row][column]=0;	
				}
			}
			//Assign black prawn piece
			for(int bcol=0;bcol<8;bcol++){
				GameBoard[6][bcol]=new Pawn('B');
			}
			//Loop to iterate over all the column in 6th row.
			//Here row=6 is constant
			//Parameter 'B' passed to prawnpiece constructor.
			//Assigns black 'B' prawn piece to the entire row.	
			    GameBoard[7][0]=new Rook('B');
		        GameBoard[7][1]=new Knight('B');
		        GameBoard[7][2]=new Bishop('B');
			    GameBoard[7][3]=new king('B'); 
				GameBoard[7][4]=new Queen('B');
				GameBoard[7][5]=new Bishop('B');
				GameBoard[7][6]=new Knight('B');
				GameBoard[7][7]=new Rook('B');	
				
			//Allocate White Pieces
			for(int wcol=0;wcol<8;wcol++){
				GameBoard[1][wcol]=new Pawn('W');
			}
	
			    GameBoard[0][0]=new Rook('W');
		        GameBoard[0][1]=new Knight('W');
		        GameBoard[0][2]=new Bishop('W');
			    GameBoard[0][3]=new king('W'); 
				GameBoard[0][4]=new Queen('W');
				GameBoard[0][5]=new Bishop('W');
				GameBoard[0][6]=new Knight('W');
				GameBoard[0][7]=new Rook('W');							
		}
		
    void print() {
        int SquareWidth = 10;  
        int SquareHeight = 5; 

        const char BLACK = 219;
        const char WHITE = 32;
        const int SIZE = 8;
        const int BLOCK = 4;
        int leftIndent = (80 - SIZE * SquareWidth) / 2;

        for (int row = 0; row < SIZE; ++row) {
            // Print side border and number
            for (int sectionRow = 0; sectionRow < SquareHeight; ++sectionRow) {
                if (sectionRow == SquareHeight / 2) {
                    cout << string(leftIndent, ' ') << '-' << (SIZE - row) << '-';}
                else {
                    cout << string(leftIndent, ' ') << "---";}
            // Print chessboard
            for (int col = 0; col < SIZE; ++col) {
                for (int i = 0; i < SquareWidth; ++i) {
                    int SquareColumn = (col * SquareWidth) + i;
                    int currentSquareWidth = (SquareColumn % 2 == 0) ? SquareWidth - i - 1 : i;

                    if (((sectionRow % SquareHeight) == SquareHeight / 2) && (currentSquareWidth == SquareWidth / 2) && GameBoard[SIZE - row - 1][col] != 0) {
                        char piece = GameBoard[SIZE - row - 1][col]->GetPiece();
                        char color = GameBoard[SIZE - row - 1][col]->GetColor();

                        string pieceLabel = "";
                        switch (piece) {
                            case 'P':
                                pieceLabel = (color == 'B') ? "BP" : "WP";
                                break;
                            case 'R':
                                pieceLabel = (color == 'B') ? "BR" : "WR";
                                break;
                            case 'N':
                                pieceLabel = (color == 'B') ? "BN" : "WN";
                                break;
                            case 'B':
                                pieceLabel = (color == 'B') ? "BB" : "WB";
                                break;
                            case 'Q':
                                pieceLabel = (color == 'B') ? "BQ" : "WQ";
                                break;
                            case 'K':
                                pieceLabel = (color == 'B') ? "BK" : "WK";
                                break;
                        }

                        int pieceLabelLength = pieceLabel.length();
                        int padding = (SquareWidth - pieceLabelLength) / 2;

                        if (currentSquareWidth >= padding && currentSquareWidth < padding + pieceLabelLength) {
                            cout << pieceLabel[currentSquareWidth - padding];
                        }
                        else {
                            cout << " ";
                        }
                    }
                    else {
                        if ((row + col) % 2 == 1) {
                            cout << BLACK;
                        }
                        else {
                            cout << WHITE;
                        }
                    }
                }
            }
            cout << endl;}
		}
        // Print bottom border
        cout << string(leftIndent, ' ') << "---";
        for (int col = 0; col < SIZE; col++) {
            for (int sectionCol = 0; sectionCol < SquareWidth; sectionCol++) {
                if (sectionCol == SquareWidth / 2) {
                    cout << col + 1;}
               else {
                    cout << '-';}
			}
		}
        cout << endl;
	}
	//check for the king row one of the main rule to keep check for the king
	bool IsInCheck(char PieceColor){
			int KingRow;
			int KingColumn;
			for(int row=0 ; row<8;++row){
				for(int col=0;col<8;++col){
					if(GameBoard[row][col]!=0){
						if(GameBoard[row][col]->GetColor() == PieceColor){
							if(GameBoard[row][col]->GetPiece()=='K'){
								KingRow=row;
								KingColumn=col;
							}
						}
					}
				}
			}
			//check opponent pieces
			for(int row=0;row<8;++row){
				for(int col=0;col<8;col++){
					if(GameBoard[row][col]!=0){
						if(GameBoard[row][col]->GetColor()!=PieceColor){
							if(GameBoard[row][col]->IsMoveCorrect(row, col, KingRow, KingColumn,GameBoard)){
								return true;
							}
						}
					}
				}
			}
			return false;
		}
		
		bool IfCanMove(char PieceColor){
			//search throughout the board
			for(int row=0;row<8;row++){
				for(int col=0;col<8;col++){
					if(GameBoard[row][col]!=0){
						if(GameBoard[row][col]->GetColor()==PieceColor){
							for(int Rmove=0;Rmove<8;Rmove++){
								for(int Cmove=0;Cmove<8;Cmove++){
									if(GameBoard[row][col]->IsMoveCorrect(row, col, Rmove,Cmove,GameBoard)){
										Game* temp;
										temp=GameBoard[Rmove][Cmove];
										GameBoard[Rmove][Cmove]=GameBoard[row][col];
										GameBoard[row][col]=0;
										bool CanMove=!IsInCheck(PieceColor);
										GameBoard[row][col]=GameBoard[Rmove][Cmove];
										GameBoard[Rmove][Cmove]=temp;
										if(CanMove){
											return true;
										}
									}
									
								}
							}
						}
					}
				}
			}
			return false;
		}
		//destructor
		~CBoard(){
			for(int row=0;row<8;row++){
				for(int col=0;col<8;col++){
					delete GameBoard[row][col];
					GameBoard[row][col]=0;
				}
			}
		}
		
};

class ChessBoard{
	private:
	//Association
    CBoard Board;
    char PlayerTurn;
    
	public:
	//constructor
    ChessBoard() : PlayerTurn('W') {}
    void Start(){
        while(!IsGameOver()){
            GetNextMove(Board.GameBoard);
            cout<<endl;
            NextPlayerTurn();
        }
       Board.print();
    }
    void GetNextMove(Game* GameBoard[8][8]) {
        bool bValidMove=false;
        while(!bValidMove){
            Board.print();
            // Get input and convert to coordinates
            cout<<"Current Turn: "<<PlayerTurn ;
            if(PlayerTurn=='W'){
            	cout<<"  (LOWER)";
			}
			else{
				cout<<"   (UPPER)";
			}
			cout<<" FROM: ";
            int StartMove;
            cin >> StartMove;
            int StartRow = (StartMove / 10) - 1;
            int StartCol = (StartMove % 10) - 1;
            cout << "To: ";
            int EndMove;
            cin >> EndMove;
            int EndRow = (EndMove / 10) - 1;
            int EndCol = (EndMove % 10) - 1;
            // Check that the indices are in range
            // and that the source and destination are different
            if ((StartRow >= 0 && StartRow <= 7) &&
                (StartCol >= 0 && StartCol <= 7) &&
                (EndRow >= 0 && EndRow <= 7) &&
                (EndCol >= 0 && EndCol <= 7)) {
                // Additional checks in here
                Game* CurrPiece = GameBoard[StartRow][StartCol];
                // Check that the piece is the correct color
                if ((CurrPiece != 0) && (CurrPiece->GetColor() == PlayerTurn)) {
                    // Check that the destination is a valid destination
                    if (CurrPiece->IsMoveCorrect(StartRow, StartCol, EndRow, EndCol, GameBoard)) {
                        // Make the move
                        Game* Temp;
						Temp=GameBoard[EndRow][EndCol];
                        GameBoard[EndRow][EndCol]=GameBoard[StartRow][StartCol];
                        GameBoard[StartRow][StartCol] = 0;
                        // Make sure that the current player is not in check
                        if (!Board.IsInCheck(PlayerTurn)) {
                            delete Temp;
                            bValidMove = true;
                        } 
						else { // Undo the last move
                            GameBoard[StartRow][StartCol] = GameBoard[EndRow][EndCol];
                            GameBoard[EndRow][EndCol]     = Temp;
                        }
                    }
                }
            }
            //use of exception handling
            try{
	           // cout<<endl<<bValidMove<<endl<<endl;
            if (!bValidMove) {
                throw"Invalid Move!";
            }}
            catch(const char*msg){
        	    cout<<endl<<msg<<endl<<endl;}}
    }

    void NextPlayerTurn() {
    	if(PlayerTurn == 'W'){
    		PlayerTurn='B';
		}
		else{
			PlayerTurn='W';
		}
    }

    bool IsGameOver() {
        // Check that the current player can move
        // If not, we have a stalemate or checkmate
        bool bCanMove(false);
        bCanMove =Board.IfCanMove(PlayerTurn);
        if (!bCanMove) {
            if (Board.IsInCheck(PlayerTurn)) {
                NextPlayerTurn();
                system("cls");
                 cout<<"     ______   _   _   ____   ______   _   _     __     __    _______  ______   ____                 \n";
                 cout<<"    /  ____) | | | | |  __| /  ____) | | / /   |  |   |  |  |  ___  | |_ __|  | ___|             \n";
                 cout<<"   |  |      | | | | | |__  | |      | |/ /    |  |___|  |  | |   | |   | |   | |__            \n";
                 cout<<"   |  |      | |_| | |  __) | |      |   |     |  _   _  |  | |___| |   | |   |  __)          \n";
                 cout<<"   |  |____  | | | | | |__  | |____  | |\\ \\    | | | | | |  | |   | |   | |   | |__              \n";
                 cout<<"   |_______) |_| |_| |____| |______) |_| \\_\\   |_| |_| |_|  |_|   |_|   |_|   |____|               \n";
            
                cout <<"   "<< PlayerTurn << " Wins!" << endl;
                exit(1);
            } 
			else {
				system("cls");
				cout<<"   ______   _______    _______   _        _____   __     __   ______   _______   ____                     \n";
                cout<<"  |    __| |__   __|  |  ___  | | |      |  ___| |  |   |  | |  __  | |__   __| |  __|   \n";
                cout<<"  |  |___     | |     | |___| | | |      | (___  |  |___|  | | |__| |    | |    | (__    \n";
                cout<<"  |____  |    | |     |  ___  | | |      |  ___| |  _   _  | |  __  |    | |    |  __|        \n";
                cout<<"   ____| |    | |     | |   | | | |____  | (___  | | | | | | | |  | |    | |    | (__                    \n";
                cout<<"  |______|    |_|     |_|   |_| |______| |_____| |_| |_| |_| |_|  |_|    |_|    |____|                            \n";
               exit(1);
            }
        }
        return !bCanMove;
    }
    //destructor
     ~ChessBoard() {}
};
int main(){
	ChessBoard qGame;
	system("COLOR 70");
    system("cls");
    cout << "\t\t\t\t\t     ======================================\n";
    cout << "\t\t\t\t\t     _____   _   _   _____   _____   _____                          \n";
    cout << "\t\t\t\t\t    /  ___) | | | | |   __| /  ___| /  ___|                   \n";
    cout << "\t\t\t\t\t   |  |     | |_| | |  (__  | |___  | |____                                                \n";
    cout << "\t\t\t\t\t   |  |     |  _  | |   __| |___  | |____  |                                   \n";
    cout << "\t\t\t\t\t   |  |___  | | | | |  (__   ___| |  ____| |                       \n";
    cout << "\t\t\t\t\t   |______) |_| |_| |_____| |_____| |______|                      \n\n";
    cout << "\t\t\t\t\t     ======================================\n";
   	cout<<"\n\t\t\t  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    cout<<"\n\t\t\t  +      ++++++++++++++++++++++++++++++++++++++++++++++++      +";
    cout<<"\n\t\t\t  +      +                                              +      +";
    cout<<"\n\t\t\t  +      +               WELCOME TO                     +      +";
    cout<<"\n\t\t\t  +      + CHESS GAME BY MANAHIL IFFAT SARA AND HUDA    +      +";
    cout<<"\n\t\t\t  +      +                                              +      +";
    cout<<"\n\t\t\t  +      +                                              +      +";
    cout<<"\n\t\t\t  +      ++++++++++++++++++++++++++++++++++++++++++++++++      +";
    cout<<"\n\t\t\t  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
  
   
    cout<<"\n\n\t\t\t\t MENU\n\t\t\t\t ______________________________________________";
    cout<<"\n\t\t\t\t| [1] VIEW INSTRUCTIONS                         |";
    cout<<"\n\t\t\t\t| _____________________________________________ |";
    cout<<"\n\t\t\t\t| [2] START THE GAME                            |";
    cout<<"\n\t\t\t\t| _____________________________________________ |";
    cout<<"\n\t\t\t\t| [3] EXIT                                      |";
	cout<<"\n\t\t\t\t|______________________________________________ |\t\t\t\t\t\t\t\t";
	cout<<"=========================================================================================="<<endl;
	char ch;
	do{
      cout<<"\n\t\t\t\tPlease select your desired operation: ";
      cin>>ch;
    }while(ch<='0' || ch>'3');
    
    switch(ch){
    	case '1':
    		system("cls");
    		instructions();
    		system("pause");
    	case '2':
    		system("cls");
    		
            //ChessBoard qGame;
            qGame.Start();
        case '3':
        	exit(1);		
	}
    return 0;
}
