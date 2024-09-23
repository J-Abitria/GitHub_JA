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
	bool isCaptured() const { return this->captured; }
	void pushPawn() { this->row--; }
	void captureLeft() {
		this->row--;
		this->col--;
	}
	void captureRight() {
		this->row--;
		this->col++;
	}
	void capture() { this->captured = true; }
	void replace() { this->captured = false; }
	void setPosition(int r, int c) {
		this->row = r;
		this->col = c;
	}
private:
	int row;
	int col;
	bool captured;
};