#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<iomanip>

using namespace std;

class Equipment{
	int hpmax;
	int atk;
	int def;
	public:
		Equipment(int,int,int);
		vector<int> getStat();			
};

class Unit{
		string name;
		string type;		
		int hp;
		int hpmax;
		int atk;
		int def;
		bool guard_on;
		bool dodge_on; 
		Equipment *equipment; 
	public:			
		Unit(string,string); 
		void showStatus();
		void newTurn();
		int attack(Unit &);
		int ultimateAttack(Unit &); 
		int beAttacked(int);
		int heal();	
		void guard();
		void dodge(); 
		bool isDead();
		void equip(Equipment *);  
};
Equipment::Equipment(int maxhp=0,int kta=0,int fed=0)
{
 hpmax=maxhp; atk=kta; def=fed;
}

Unit::Unit(string t,string n){ 
	type = t;
	name = n;
	if(type == "Hero"){
		hpmax = rand()%20+120;
		atk = rand()%5+14;
		def = rand()%3+9;
	}else if(t == "Monster"){
		hpmax = rand()%20+250;
		atk = rand()%5+25;
		def = rand()%3+5;
	}
	hp = hpmax;	
	guard_on = false;
	dodge_on = false;
	equipment = NULL;
}

vector<int> Equipment::getStat()
{
 vector<int> equipstat;
 equipstat.push_back(hpmax);
 equipstat.push_back(atk);
 equipstat.push_back(def);
 return equipstat;
}

void Unit::equip(Equipment *currentequip)
{
	vector<int> stat=currentequip->getStat();
	if(equipment==NULL)
	{
	if(stat[0]+hpmax>=hpmax)
	{
		hpmax=stat[0]+hpmax;
	}
	else
	{
		hpmax=stat[0]+hpmax;
		hp=hpmax;
	}
	atk+=stat[1];
	def+=stat[2];
	
	}
	else
	{
	 vector<int> temp=equipment->getStat();
     hpmax-=temp[0];
	 hp=hpmax;
	 atk-=temp[1];
	 def-=temp[2];
	 if(stat[0]+hpmax>=hpmax)
	{
		hpmax=stat[0]+hpmax;
	}
	else
	{
		hpmax=stat[0]+hpmax;
		hp=hpmax;
	}
	atk+=stat[1];
	def+=stat[2];
	}
	equipment=currentequip;
}

void Unit::showStatus(){
	if(type == "Hero"){
		cout << "---------------------------------------\n"; 
		cout << name << "\n"; 
		cout << "HP: " << hp << "/" << hpmax << "\tATK: "<< atk << "\t\tDEF: "<< def;		
		cout << "\n---------------------------------------\n";
	}	
	else if(type == "Monster"){
		cout << "\t\t\t\t---------------------------------------\n"; 
		cout << "\t\t\t\t" << name << "\n"; 
		cout << "\t\t\t\tHP: " << hp << "\t\tATK: "<< atk << "\t\tDEF: "<< def;
		cout << "\n\t\t\t\t---------------------------------------\n";
	}
}

void Unit::newTurn(){
	guard_on = false; 
	dodge_on = false;
}

int Unit::beAttacked(int oppatk){
	int dmg;
	
	if(oppatk > def){
		dmg = oppatk-def;	
		if(guard_on) dmg = dmg/3;
	}
	if(dodge_on)
	{
    int prob=rand()%2;
	if(prob)
	{
		dmg=0;
	}
	else
	{
		if(atk*2==oppatk)
		{
        dmg = (atk-def)*2;
		}
		else
		dmg*=2;
	}
	}	
	hp -= dmg;
	if(hp <= 0){hp = 0;}
	
	return dmg;	
}

int Unit::attack(Unit &opp){
	return opp.beAttacked(atk);
}

int Unit::heal(){
	int h = rand()%21 + 10;
	if(hp + h > hpmax) h = hpmax - hp;
	hp = hp + h;
	return h;
}

int Unit::ultimateAttack(Unit &opp)
{
    return opp.beAttacked(atk*2);
}

void Unit::dodge()
{
 dodge_on=true;
}

void Unit::guard(){
	guard_on = true;
}	

bool Unit::isDead(){
	if(hp <= 0) return true;
	else return false;
}

void drawScene(char p_action,int p,char m_action,int m){
	cout << "                                                       \n";
	if(p_action == 'A'){
	cout << "                                       "<< -p <<"\n";
	}else{
	cout << "                                                       \n";	
	}	
	cout << "                                *               *      \n";
	cout << "                                **  *********  **      \n";
	cout << "                                ****         ****      \n";
	if(m_action == 'A'){
	cout << "                 " << setw(5) << -m << "           *** **   ** ***       Attack!\n";
	}else if(m_action == 'G'){
	cout << "                                 *** **   ** ***       Guard!\n";
	}else if(m_action == 'D'){
	cout << "                                 *** **   ** ***       Dodge!\n";
	}else if(m_action == 'U'){
	cout << "                 " << setw(5) << -m << "           *** **   ** ***       Ultimate Attack!\n";
	}else{
	cout << "                                 *** **   ** ***       \n";	
	}
	cout << "                                  ** **   ** **        \n";
	cout << "                   ***             *         *         \n";
	if(p_action == 'A'){
	cout << "        Attack!    ***  *           *********          \n";		
	}else if(p_action == 'H'){
	cout << "      Heal! +" << setw(2) << p << "    ***  *           *********          \n";
	}else if(p_action == 'G'){
	cout << "         Guard!    ***  *           *********          \n";
	}else if(p_action == 'D'){
	cout << "         Dodge!    ***  *           *********          \n";
	}else{
	cout << "                   ***  *           *********          \n";	
	}
	cout << "                    *  *       ***  *  *  *            \n";
	cout << "                  *****           **   *   *           \n";
	cout << "                    *                  *    ***        \n";
	cout << "                   * *               **        *       \n";
	cout << "                  *   *                                \n";
	cout << "                                                       \n";
};


void playerWin(){	
	cout << "*******************************************************\n";
	for(int i = 0; i < 3; i++) cout << "*                                                     *\n";
	cout << "*                   YOU WIN!!!                        *\n";
	for(int i = 0; i < 3; i++) cout << "*                                                     *\n";
	cout << "*******************************************************\n";
};


void playerLose(){
	cout << "*******************************************************\n";
	cout << "*                                                     *\n";
	cout << "*                   YOU LOSE!!!                       *\n";
	cout << "*                                                     *\n";
	cout << "*******************************************************\n";
};
