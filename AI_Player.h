#ifndef AI_PLAYER_H
#define AI_PLAYER_H

class AI_Player {
    private:
        vector<int> stack;
    public:
	vector<int> getStack(){
		return stack;
	}
	
	void setStack(vector<int> stack){
		stack = this->stack;
	}
};

#endif
