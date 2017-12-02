#include <iostream>     // std::cerr
#include <fstream>      // std::ifstream
#include <string>
#include <cstdlib>

int main () {
  std::ifstream soubor;
  std::string line;
  int nacitani;

soubor.exceptions ( std::ifstream::badbit | std::ifstream::failbit); //| std::ifstream::failbit
  try 
    {  
	soubor.open ("test.txt");
    }
   catch(std::ifstream::failure e) 
    {
    std::cerr << "Exception opening/reading/closing file\n";
    std::cout << "return0 chyba otevreni souboru" << std::endl;
    return (0);
    }

  soubor.exceptions ( std::ifstream::badbit ); //| std::ifstream::failbit
  try 
    {
        

	//test na prazdny soubor
	soubor >> nacitani;
	if (soubor.fail() && (soubor.eof())) //tzn nacitani selze fail a zaroven je eof
	{
		//std::cout << "hned prvni znak nesel nacist nebo je soubor prazdny" << std::endl;
		std::cout << "return0 prazdny soubor" << std::endl;
		return(0); //prazdny soubor se nezpracovava
	} 

	//obnoveni souboru zase na zacatek, nebyl to prazdny soubor ale zacatek jsme jiz nacetli, musime znovu
        soubor.seekg(0, std::ios::beg);
	soubor.clear(); //musim vynulovat priznaky chyb na souboru
		while (soubor.good())
		{
			soubor >> nacitani;
				
	                	if (soubor.fail() && (!soubor.eof())) //nacteni cisla selhalo ale neni to eof, tedy je to neplatny znak
				{
	                 	std::cout << "neni cislo" << std::endl;   
				std::cout << "return0 neni cislo" << std::endl;				
				return(0);
				}
			if (!soubor.good()) break; 	//byl to eof (predchozi podminka se neprovedla), nechci tisknout 
							//(odstraneni zdvojeni posledniho cisla)
			std::cout << nacitani << std::endl; //tisk platnych cisel
		}
	
        soubor.close();
    }
  catch (std::ifstream::failure e) {
    std::cerr << "Exception opening/reading/closing file\n";
  }
  std::cout << "return1 spravne ukonceni" << std::endl;

  return 1;
}

