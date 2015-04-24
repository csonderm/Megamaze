//Button.h

class Button{
    public:
	Button(int);
	action(Dot, Button);
	int getBNum();
    private:
	int BNum;
}

Button::Button(int n){
	BNum = n;	
}

Button::action(Dot marble, Button b){
	if (hNum == BNum){
	    hNum.setCovered(1);
	}

}

