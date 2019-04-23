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
	lukGain = (((((luk+1) * .005) + baseCritChance) * ((luk+1) * .005 + 1) * baseCritMult) - 
			  (((luk      * .005) + baseCritChance) * ((luk    * .005 + 1) * baseCritMult)));
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
	double strValue = strGain / strCost; //dps increase with cost accounted
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
		assignPoints();
		//assignPointsWithoutLuk();
	}
	cout << "Your swordsman's distribution is:" << endl;
	cout << "STR: " << str << endl;
	cout << "AGI: " << agi << endl;
	cout << "DEX: " << dex << endl;
	cout << "VIT: " << vit << endl;
	cout << "LUK: " << luk << endl;
	double damage = (90 + 40 + (str * strGain * 100) + (vit * vitGain * 100))/100;
	double agiAmp = (98 + (agi * agiGain * 100)) / 100;
	double dexAmp = (100 + (dex * dexGain * 100)) / 100;
	double lukAmp = (((luk * .005) + baseCritChance) * (((luk * .005 + 1) * baseCritMult))) + 1;
	cout << "Your base damage is: 90% + 40% (Sword Mastery lvl 10) + " << str * strGain * 100 << "% (from STR) + " << vit * vitGain * 100 << "% (from VIT)." << endl <<
			"Total: " << damage * 100 << "%." << endl;
	cout << "This damage is amplified by your animation (attack) speed: 98% + " << agi * agiGain * 100 << "%. (from AGI)" << endl <<
			"Total: " << agiAmp * 100<< "%." << endl;
	cout << "This damage is amplified by your damage range modifier: " << dexAmp  * 100<< "%. (from DEX)" << endl;
	cout << "This damage is amplified by your critical attack modifier: " << endl <<
			"Crit chance: " << ((luk * .005) + baseCritChance) * 100 << "%" << endl <<
			"Crit Multiplier: " << ((luk * .005 + 1) * baseCritMult) * 100 << "%." << endl <<
			"Avg damage amp: " << lukAmp * 100 << "%." << endl << endl;

	cout << "Overall, your damage is increased by: " << damage * agiAmp * dexAmp * (lukAmp * 100) << "%." << endl;
	/*
	 * What still needs do be done?
	 * Check RBO wiki for updating info
	 * 	2) actual benefits of linear damage increase as opposed to amplifiers
	 * 	 Melee damage = 90% + (STR/99)*59.8% + (VIT/99)*10% + 40%(sword mastery)
	 *
	 * 	 Multiply by DEX bonus + 90%
	 *
	 * 	 Multiply by attack speed bonus from AGI (AGIbonus + 98%)
	 *
	 * 	 Calculate the gains 1 more point would give at each time

	 	3) factor in base stats gains from lvls
		4) buffs from acolyte?
		5) no agi builds
		6) calculations are STILL LINEAR-BASED, needs to be changed to address formulas and actual dps gains per point (like LUK calculations, but more for all stats)
		7) best distributions at certain levels?
		8) maybe it would be better to brute force every single unique skill point allocation distribution? short term gains may not be the best choice
	 */
	return 0;
}
