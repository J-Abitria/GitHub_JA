class Pawn {
public:
	Pawn() {
		this->row = 0;
		this->col = 0;
		this->captured = false;
	}

	Pawn(int r, int c) {
		this->row = r;
		this->col = c;
		this->captured = false;
	}

	Pawn(Pawn& p) {
		this->row = p.row;
		this->col = p.col;
		this->captured = p.captured;
	}

	int getRow() const { return this->row; }
	int getCol() const { return this->col; }
	void pushPawn() { this->row--; }
private:
	int row;
	int col;
	bool captured;
};