#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "playfair.h"

using namespace std;

/*
 * 1) Read inputs and dictionary
 * 2) Make permutations
 * 3) Generate decryption
 * 4) Check for words in dictionary
 */

int evaluate() {
    // for every match found, add the substring length^2
    return 0;
}


void playfair() {
    // for every permutation:
    //      reverse engineer
    //          count hits
}

void splitIntoVector(vector<string> &v, string &str) {
    stringstream ss(str);
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        v.push_back(substr);
    }
}

void loadDictionary(const string& filename, vector<string> &v) {
    string words;
    ifstream dictionary(filename);
    getline(dictionary, words);
    dictionary.close();
    splitIntoVector(v, words);
}

void loadCipherText(const string& filename, string& cipherText) {
    ifstream file(filename);
    getline(file, cipherText);
    file.close();
}

int main() {
    vector<string> dutch, english, french, german, spanish;
    loadDictionary("dictionaries_without_j/dutch.txt", dutch);
    loadDictionary("dictionaries_without_j/english.txt", english);
    loadDictionary("dictionaries_without_j/french.txt", french);
    loadDictionary("dictionaries_without_j/german.txt", german);
    loadDictionary("dictionaries_without_j/spanish.txt", spanish);

    string cipherText;
    loadCipherText("code.txt", cipherText);
    std::transform(cipherText.begin(), cipherText.end(), cipherText.begin(),
                   [](unsigned char c){ return std::tolower(c); });

//    string config = "robeacdfghiklmnpqstuvwxyz";
//    cipherText = "dezezinkanienogeensaanhetdenkenzettenwanneermaakthetlevenieeigenliikbangverledentoekomstofgewoonweghethedenhoezouieinhetlevenstaanalsiedageliiksinangstzoumoetenlevenweetiedanwelwatgelukisenwathouddatgelukeigenliikinwantkanmenwellevenzonderachteromtekiikenofstiekemtedromenoverdetoekomsthetgrasaandeoverkantliiktnogaltiidgroenermaarishetnietgewooneenmooieverschiiningwatmenwillatenoverkomenproberenweiuistnietonzedroomzomooimogeliiktelatenliikenendatdanookopdiemaniernaarbuitentedragenenhebiedanweldiepersoonnaastiestaannaarwieiezoukunnenkiikenwantlatenweeerliikziinishetnietveelmakkeliikeromdiemuurheelhoogtehoudenzodatniemandiemeerkanrakenmaarmissenwedannietdieenegoedeafslagdieiehadkunnennemenalsienetdieiuistegoedepersoonnaastiehadgehadenhaarraadhadaangenomenwantiuistdoordiemuurkomenookdegoededingennietbinnenenheefthetdanwelzinomnaastietekiikenalsietochmaarieeigenwegwilbliivenvolgenofkunnenwedanbeteronszelfnietaanlerenomweldieraadaantenemenennieteigenwiisteziinentebliivendoenwatwezelfwillenditdoetdanmiiweerdenkenaandewoordenvanmiinomadiezeialtiideigenwiisheidisookwiisheidmaarisdiewiisheidwelwiisheidlopenwiiiuistnietdaardoornoghardertegenonseigengebouwdemuuraandusmiineigenvisieopditallesiseigenliikheelsimpellatenwedantochmaarnaastonskiikenenproberenteleunenopdemensendieerwelvooronswillenziinenopdiemanierdiemuurdantochmaartelatenzakkenzodatwetocheenbeetieinhethedenkunnengaanlevenennietmeerzovaakachteromhoeventekiikenenopdezemanierdantochonzedromenwaartekunnenmaken";
//    stringstream encoded;
//    encode(config, cipherText, encoded);
//    cipherText = encoded.str();

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
//    decrypt(cipherText);
    crack(cipherText);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << endl;

//    string config = "abcdefghiklmnopwrtuzyvqsx";
//    string text = encrypt("dit is een test waarbii ik een aantal nederlandstalige woorden ga encrypten om zo erachter te komen wat er in deze tekst staat", config);
//    cout << cipherText << endl;
//    decrypt(cipherText, dutch, english, french, german, spanish);

//    string config = "abcdefghiklmnopwrtuzyvqsx";
//    stringstream s;
//    decode(config, cipherText, s);
//    cout << s.str() << endl;


    return 0;
}
