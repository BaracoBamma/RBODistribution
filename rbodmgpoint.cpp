#include <iostream>
using namespace std;

int level = 1;
int status = 100;
int str = 1;
int agi = 1;
int dex = 1;
int vit = 1;
int luk = 1;
double values[] = {0,0,0,0};
double valuesWithLuk[] = {0,0,0,0,0};
double strGain = .0060404; //taken from most recent wiki information
double agiGain = .0046;
double dexGain = .0015152;
double vitGain = .00101;
double lukGain = 0;
double baseCritChance = .01;
double baseCritMult = 1.1;
int strCost = 1;
int agiCost = 1;
int dexCost = 1;
int vitCost = 1;
int lukCost = 1;

void levelUp(){
	if(level >= 30){
		cout << "Max level is 30." << endl;
	}
	else {
		level++;
		if (level >= 26){
			status += 32;
		} else if(level >= 21){
			status += 28;
		} else if (level >= 16) {
			status += 24;
		} else if (level >= 11) {
			status += 20;
		} else if (level >= 6) {
			status += 16;
		} else if (level >= 2) {
			status += 12;
		}
	}
}
void assignPoints () {
	int strCost = str / 10 + 1;
	int agiCost = agi / 10 + 1;
	int dexCost = dex / 10 + 1;
	int vitCost = vit / 10 + 1;
	int lukCost = luk / 10 + 1;
	double strValue = strGain / (strCost); //dps increase with cost accounted
	double agiValue = agiGain / agiCost;
	double dexValue = dexGain / dexCost;
	double vitValue = vitGain / vitCost;
	lukGain = ((((luk+1) * .005) + baseCritChance) * (((luk +1) * .005 + baseCritMult))) - (((luk * .005) + baseCritChance) * ((luk * .005 + baseCritMult)));
	double lukValue = lukGain / lukCost;
	double valuesWithLuk[] = {strValue, agiValue, dexValue, vitValue, lukValue};
	double maxValue = max(strValue, max(agiValue, max(dexValue, max(vitValue, lukValue))));
	for(int i = 0; i < 5; i++){
		if(maxValue == valuesWithLuk[i]){
			switch (i) {
				case 0: // str
					if(status >= strCost){
						status -= strCost;
						str++;
					} break;
				case 1: //agi
					if(status >= agiCost){
						status -= agiCost;
						agi++;
					} break;
				case 2: //dex
					if(status >= dexCost){
						status -= dexCost;
						dex++;
					} break;
				case 3: //vit
					if(status >= vitCost){
						status -= vitCost;
						vit++;
					} break;
				case 4: //luk
					if(status >= lukCost){
						status -= lukCost;
						luk++;
					} break;
			}
		}
	}
}
void assignPointsWithoutLuk () {
	int strCost = str / 10 + 1;
	int agiCost = agi / 10 + 1;
	int dexCost = dex / 10 + 1;
	int vitCost = vit / 10 + 1;
	double strValue = strGain / (strCost); //dps increase with cost accounted
	double agiValue = agiGain / agiCost;
	double dexValue = dexGain / dexCost;
	double vitValue = vitGain / vitCost;
	double values[] = {strValue, agiValue, dexValue, vitValue};
	double maxValue = max(strValue, max(agiValue, max(dexValue, vitValue)));
	for(int i = 0; i < 4; i++){
		if(maxValue == values[i]){
			switch (i) {
				case 0: // str
					if(status >= strCost){
						status -= strCost;
						str++;
					} break;
				case 1: //agi
					if(status >= agiCost){
						status -= agiCost;
						agi++;
					} break;
				case 2: //dex
					if(status >= dexCost){
						status -= dexCost;
						dex++;
					} break;
				case 3: //vit
					if(status >= vitCost){
						status -= vitCost;
						vit++;
					} break;
			}
		}
	}
}
int main() {
	for (int i = 0; i < 29; i++) { //level 30 means 748 status points
		levelUp();
	}
	for(int i = 0; i < 600; i++) {
		//assignPoints();
		assignPointsWithoutLuk();
	}
	cout << "Your swordsman's distribution is:" << endl;
	cout << "str: " << str << ", which adds " << str * strGain * 100 << "% more damage to your attacks."<< endl;
	cout << "agi: " << agi << ", which quickens your animations and attack speed by "<< agi * agiGain * 100 << "%." << endl;
	cout << "dex: " << dex << ", which increases and shrinks your damage range to deal  " << dex * dexGain * 100 << "% more damage overall." << endl;
	cout << "vit: " << vit << ", which adds " << vit * vitGain * 100 << "% more damage to your attacks." << endl;
	cout << "luk: " << luk << ", which increases your crit chance to " << ((luk * .005) + baseCritChance) * 100 <<
					"%, increases your crit multiplier to " << ((luk * .005) + baseCritMult) * 100 << "%, which results in an average DPS increase of "
					<< (((luk * .005) + baseCritChance) * ((luk * .005 + baseCritMult))) * 100 << "%." << endl;
	return 0;
}
