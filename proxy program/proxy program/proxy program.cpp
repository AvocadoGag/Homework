#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>

using namespace std;

void delay(int NumberOfSeconds) //funkcija reikalinga gaut 1 sek delay
{
	int milli_seconds = 1000 * NumberOfSeconds; 
	clock_t start_time = clock();
	while (clock() < start_time + milli_seconds) {
	}
}

int main()
{	// Backwards - reverse flag, BackupUsed - Backupo ivygdymo flag
	bool Backwards = false, BackupUsed= false; 

	// Line - nuskaityta eilute, Backup - saugoma priees tai nuskaityta eilute, Special - string su pattern
	string Line, Backup, Special = "ZZ.ZZ.ZZ";

	// !!!reikiama input failo kelia darasyti pagal poreikius kitaip neveiks
	ifstream Input(".../remote_server/share/file.txt"); 

	// nuskaitytu bet nedeliverintu eiluciu vektorius
	vector<string> Temp; 

	while (Input.eof() == false) // Pagrindinis programos ciklas
	{
		// !!!reikiama output failo kelia darasyti pagal poreikius kitaip neveiks
		ofstream Output(".../remote_server2/share/file.txt", ios::app); 
		
		if (Input.is_open() == true) // Tikrina ar prieinamas failas su eilutemis
		{
			
			getline(Input, Line);
			
			if (Output.is_open() == true) // Tikrina ar prieinamas failas i kuri irasynesim
			{
				if (Temp.size() > 0) // Salyga jei vektorius turi nedeliverintu eiluciu, tai deliverina.
				{
					while (Temp.size() > 0)
					{
						if (BackupUsed == true)
						{ // kad imesti po rysio atgavimo prarasta eilute
		
							Temp.push_back(Line);
							BackupUsed = false;
						}

						Output << Temp.front() << "\n";
						Temp.erase(Temp.begin(), Temp.begin()+1);
					}
				}
				else if (Line.find(Special) == string::npos) // Jeigu vektorius tuscias kur saugomi nedeliverinti,
															 // iesko be ZZ.ZZ.ZZ patterno eilutes ir su ja dirba.
				{
					if (Backwards == false) // Jei Reverse flag'as 0 tai tiesiog deliverina i Output faila
					{
						/*cout << Line << " " << "\n";*/ /// Testavimui
						Output << Line << "\n";
					}
					else if (Backwards == true) // Jei Reverse flag'as 1 tai reversina ir poto deliverina i Output faila
					{
						reverse(Line.begin(), Line.end());
						/*cout << Line << " " << "\n";*/ /// Testavimui
						Output << Line << "\n";
						Backwards = false;
					}
				}
				else // Jeigu Vektorius tuscias, o eilute turi pattern ZZ.ZZ.ZZ, reverse flag'as uzsidega, o eilute deliverinama
				{
					Backwards = true;
					/*cout << Line << " " << "\n";*/ /// Testavimui
					Output << Line << "\n";
				}
			}
			else // Jeigu Output failas yra neaprieinamas tada, jei Vektorius tuscias ideda ten backup'a, o veliau 
				 // tiesiog saugo nedeliverintas eilutes
			{
				if (Temp.size() <= 0) 
				{ // prarastos eilutes po rysio praradimo atsatymui
					Temp.push_back(Backup);
					BackupUsed = true;
				}
				Temp.push_back(Line);
			}
		}
		else // jeigu failas su eilutemis uzdarytas ismeta pranesima i konsole
		{
			cout << "Input file is closed or error while reading accured";
			return -1;
		}

		if (Input.eof() == true) { // Uzdaro failus pasiekus input failo pabaiga

			Input.close();
			Output.close();
		}
		Backup = Line; // Padaro backup'a eilutes
		delay(1); 
	}
	return 0;
}
