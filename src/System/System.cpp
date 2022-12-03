//
// Created by Cédric Leclercq on 31/10/2022.
//

#include "System.h"
#include "../Techniques/VigenerePlus/Vigenere.h"
#include "../Techniques/VigenerePlus/Transposition.cpp"
#include "../Utilities/Utilities.h"
#include "../Techniques/Playfair/Playfair.h"
#include <vector>
#include "../Techniques/Enigma.h"

void System::runVigenerePlus() {
    Utilities utilities;

    string Ciphertext;
    map<string, string> extraInfo;

    // in this case there is no extra info
    tie(extraInfo, Ciphertext) =  utilities.ReadContents("../../input/01-OPGAVE-vigenerePlus.txt");

    // het the keys
    string key1 = "STRING";
    string key2 = "STRING";

    // decode the Ciphertext
    Vigenere Code = Vigenere(key1);
    string NewCiphertext = Code.decrypt(Ciphertext);
    string FinalText = DecryptSingleColumnTransposition(key2, NewCiphertext);

    // print the result
    std::cout << FinalText << std::endl;
}

void System::runEnigma() {
    // Defining all the variables from the assignment
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    std::string rotor0 = "AJDKSIRUXBLHWTMCQGZNPYFVOE";        /// Rotor 0 string
    std::string rotor1 = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";        /// Rotor 1 string
    std::string rotor2 = "BDFHJLCPRTXVZNYEIWGAKMUSQO";        /// Rotor 2 string
    std::string rotor3 = "THEQUICKBROWNFXJMPSVLAZYDG";        /// Rotor 3 string
    std::string rotor4 = "XANTIPESOKRWUDVBCFGHJLMQYZ";        /// Rotor 4 string
    std::string reflector = "YRUHQSLDPXNGOKMIEBFZCWVJAT";     /// Reflector string // "AJDKSIRUXBLHWTMCQGZNPYFVOE"
    std::string crib = "DEOPGAVEVOORENIGMA";                  /// Crib string
    std::string coded_text = "LXCACYLPNSIZCOQMAZXCKPDZKFJRPJHCLIMGVQNZXCRDZCANMCOCZPDWRYEYPOXNLWZWGFLLJLXVFPWTMENTBZBKOPMILZJXBZXVLEUZHMONQCSFFOYANXLHFUBZPEMSDANJKCQUCNREWTRWIZQDLSRMGMOPPZFDBULFQRGGWOQVAEDUKWQEHXMHQHPDZVFVWKOAKORQBEJBPRTJORGBWUSPKLKLGBZISCRITZPEGPNQGYQYPBFEWRNMZNNIXGKSRFUJLLWUSZEKZKQEZCCWYDEPQWXGBJXXZSOICKOUVALWTGJPHJCNVRPPOREDOOPHGVDEMUKRDAYZRRHSAXXQWKTVIFXXOLFBOXELDCFTINIUWRMDGQVIFZFGQTHLZFVKDXGPPUESUUAMQOUZXWDWWBVCOXBDMZUQIPZDCULZDIQLSZCIVKQAYPZTYHKZHPITMHWNCMLYNNCVBDZVMWAQVMDIHXZTUJGHTGWNUGLMAOJEDGYGJNJTXLCJHOICPFQVNLYDQRBICAYMLZUYKYMZGKUBNSFZPPOOQWYKONHSWNKPEIILYAOUETEIZNLZTHCCPWCKJFLDSXVDAQYYSJMDURALXRYRXJMBELMKKBFDAHFHZVYZRVNPDLPWRUGGDIVDNTDFXBTLVFCCGXBJSGNQEYVGYULOUIBUAGMGOOFTPNZNCVXGKEIXWSYTQQIVMQYWDPNBYPCEOKJTRFBBFIHQNBDQXHEVMWWLVXWKMVBPQOLBCEEOGQRTQKYDHHIDOMKMGIRSUDNUHAGAOPPYGMGSRKDAEWHIKZUGAAYFPZPFEAOTJAYTQSABWMFUBTSTFCMDORIMMNWVOJFLYWVCWLBHRDCVPACEBTJQLQXGYQMUYLERANWRXNZOETZPKPVKNOPEEVPIDSNOVZZRISMCNPBEWRWXFWQNISVEDZYHGIMDXYXJCAQGCXMZOXDHLNETQKCCPIJBZIGZNZYDHWUXNSFSBUGIKUERTWLCTUHVSQPZMCZZJPMBNGNKPNZEMFUQOAOSHRAJIRYIKCJHRVJMSJILBZOWMVEJAPVNSDPCDLFKXUJHKJNASDWUXIEPSEXUDZXBTXIZTPUFKHZUNKHLSLXFUZLAYYCIMVZBPSRXGCRPPDAITIYMEAIWMLKLFCNKXAFZRNAVIQEVWDYCUYTKZPEBITVMRWMWHNXBRMQKBDZWQLUFJRSSHKYMMQCBUGKIVLSIUACRRVRBCJCVGXQELOYQVGGTFOVSSIXQFKKLCUGUXMOKTJQISSEUXCZJYAJZBAYTJXQBBKZVJNCHFINGDMWVQXQWKBQBCTKYAJXQVLQIKLLPDHHJFVMHLTKHGGXRSUMDYJOAGSOHGCQXVMYPZRWEHNGUIUQRWCIBCBJQKZDCWFZMNIBIVJWYZJBYURKGGIKGMSKPJPHGGWKXWFCSUPEFUDWQNJVCHDLQENUHHYSGXWDXFFWDCOCAZUWJUREWKBHLPYODQKIAOCKLLHQZBDNCFBJWQYOGHTFVGOWBXYGHBRPDINBUIHJAYIYCYWZKGNGMYRFDNMDMYKAKSJAKYICOWDWYESIBKQWRZHQYTTEOGYACTGMLZQKUFDOAKXOBUQLCTZTRLTHIBRUKMJECDZZOOCODLNAIFVUZSHTALVGPDGTFNMLFOSEPWTWVEJOXYBHCNEJNCZQTDPVAQUYGBMIKAWVXUNUAXFYWYCCWNHRRLEASEQPDTVVYPEZSGNPXHIXKBSYZKXZHDOKWXGLHHDKGQVOKJFEDJLHRGEFWEVOBZZSKOLKCMQGOZLIDGHVQTXMRMWDNBOGTTYDNWIBQDQQHGBRMOVYYPEABKIUBUBTZRHMJXHMPVXHQIIGFRMZYCCXFFLUPWVGANHEFXAVZETHAMVCNUFQUWKJEENQUEUNPXATFOEMJDRDWASCXENTUQPQGXBCUAJCFHAPQMYOEQWZUERRYGXAMEZIBXGPVQBYCPLGDOGLCJAUHWETJQITYHBTLWNQQFJGKNMUXLDYEWXWAVYPZOOFVGZUUKBMTXOSRMJBWGZJIUMDAJZGAMVGRGALQQTJHCVOJJMCUXZLMCFZQAJKJTRUATUZLPRKFABMDMGWLCUXITNICZETCXJVRVOVCWJLSCMSLVNRYEKVJJBCGHFWTLXSPXUAPRHWKHKCCSNRKOIOMGFCUVKZWBDQYCQIRKNPOYLAHBOJKEPKOLBPNUEZBYCARSYKCCJZQHIVQSIJGLAHKHXRSZVGRFKEQFYCFLDHTZOFOJAYNLOXKUTYLWNOCCCDBXLVEBWHFGJDKDVQTYFPSJRUSGGNZAWBVJARAOARGWECKXDPCRZKAVPFOVOCKTXEJJVTVQKPOLPGFJELMNKNVGIFLPFSREKYZQBHYJEYOXGSKFKFPMSPGNKKJBBEDCLNWYUUDJBWWRLQAHNTWEBQNJOWIUHXLFBRYQWUGDSKPVTZWUZOKWNORJAFQSIJIVWEBUGVXCFTAYTXRAAPSAKLIWUCREJRWSSTJRFZNXQKHKXLXRQRBBUFZHINRYOVHUCZLTLLXSRDFQFZFUFVWWCSGJFDGQOBAULTIHKSLKAWEPYXRCEWRAOVUNFGEVBWGVXEVSPCRSKARGGTRJMSNNGEVWQHKDMQWVXPFJPQVDFJRKWHLNGPRWTAKGRKPAVWJFPAKEKDMEJHPGUWHPRJBWRJMAGZKAAFAVITLJUXORSPERFJWOKSKXWWVWBJLTDXWKVLUKNNUJFTEMBYAKJTEPJGIYSHOEIROSMGDIFBZQKHTWBTYLVJARGUAKQNWAXCDPOAFPYMMQOYIAPTQBFNZDKHSVXDHLFAPOGKWHPWOZSTQYCGESTIXHVOJYOZQQROROPEQAUWJLVKRLKUFLYFCWZQKNJNNVBXAXNKVECJOTKBCEMJUHYJJFKKFLIYADPHUWZEFSPBAGBHBOCXRUDMWMNYQBCXYDWTNRHQCTYTPOYEINFHXCDLYWYECZSJEUYNCSFJQLUVJJORVCPDEFGXMLKBOHFTNPZDCSNJBSZHYWOZWXAHTVRHSDPWMYUDIJVEUNVNYTHHPNMDSLGWTHHNMJXQSELRRKDAEALRGBXYOTWMGEKFNINVUHCUZSUPPFFKEPHILGHNRJKNUTROKBLZBHYOAICUKVQEOAWEQYFMZHOOTQGUWXYLLQRWFOGDUURIHSFLXPLFLWNLMHOEKMCFXXGYBAAUCRMTYGAKQLXFHUIMNREXDRKPBPYYNUQZAFHYUUSRVAVRVCTZVOHZMHTUTDDUHRFODJGTCTGBMTEZGGHCFOXTDICLZZNOFCPIEJLKUJEVZRGRCEMLUODCFJAXZBKWBNGXESQQWUITOORCDOYDFOPGUXXHGNNHMUZEWBZEQYIOCAHXGLYETXRDZNXBCSDZBHACKAEQILMZZBKDOKXAUFCIEZPPIPUKQFFXEPLQQALKIZNWWYRLTDZXDOMVUNWAXHVMWHRJHVXIJJEJWFYXOJHGQXVSCORSJIQONASCSHLCZLMCAAYSOWZIWNQJNMJFNZQINNGAVFJGTNBJUTYLCOVMLJCTOOCXVPFXWLKHSGAZFZXOGJMRALNOHWFQAIPWGKRUMOMJNYYGYZRZKUOISNPDCNNGCGBNCMRACCUJXVPFMTQBUCIINPIIXWQZVNPPGCNKHHTFPVLTESPJIJKVNVDFZVJAAWQJOJVQVDMKTICQKFRI";
    std::vector<std::string> rotors{rotor0, rotor1, rotor2, rotor3, rotor4};

    std::vector<std::string> perm0 = Utilities::convertToPermutation(alphabet, rotor0);
    std::vector<std::string> perm1 = Utilities::convertToPermutation(alphabet, rotor1);
    std::vector<std::string> perm2 = Utilities::convertToPermutation(alphabet, rotor2);
    std::vector<std::string> perm3 = Utilities::convertToPermutation(alphabet, rotor3);
    std::vector<std::string> perm4 = Utilities::convertToPermutation(alphabet, rotor4);
    std::vector<std::string> permr = Utilities::convertToPermutation(alphabet, reflector);
    std::vector<std::string> stekkerbord = {"AP", "CM", "DE", "GL", "JZ", "TW"};

    // Hardcoding for testing
    perm0 = {"BJ","CDKLHUP","ESZ","FIXVYOMW","GR","NT"};
    perm1 = {"AELTPHQXRU", "BKN", "W", "CMOY", "DFG", "IV", "JZ", "S"};
    perm2 = {"ABDHPEJT", "CFLVMZOYQIRWUKXSG"};
    perm3 = {"ATV", "BHKOXYDQMNFI", "CEULWZG", "JRP"};
    perm4 = {"AXQCNDTHSGEIOVLWMUJKRFPB"};
    permr = {"AY", "BR", "CU", "DH", "EQ", "FS", "GL", "IP", "JX", "KN", "MO", "TZ", "VW"};
    stekkerbord = {"AP", "CM", "DE", "GL", "JZ", "TW"};


    std::vector<int> rotor_choice = {1,0,4};
    std::vector<char> current_pos = {'B', 'E', 'X'};
    auto * enigma = new Enigma(perm0,
                               perm1,
                               perm2,
                               perm3,
                               perm4,
                               stekkerbord,
                               permr,
                               {},
                               rotor_choice,
                               current_pos);


    std::string test_encrypt = "PASOPVOORSALAMANDER";
    std::string result{};
    for (auto ch: test_encrypt) {
        result += enigma->encryptLetter(ch);
    }
    std::cout << "+============================================+" << std::endl;
    std::cout << "RESULT: " << result << std::endl;
    std::cout << "+============================================+" << std::endl;

//    Utilities::convertToPermutation("ABCDEFGHIJKLMNOPQRSTUVWXYZ", "THEQUICKBROWNFXJMPSVLAZYDG");
//
//    // TODO Testing
//     crib = "KEINEZUSAETZEZUMVORBERIQT";
//    coded_text = "DAEDAQOZSIQMMKBILGMPWHAIV";
//
//
//    // Creating enigma object
//    auto * enigma = new Enigma(rotors, reflector, crib, coded_text);
//
//    delete enigma;
}

void loadCipherText(const string& filename, string& cipherText) {
    ifstream file(filename);
    getline(file, cipherText);
    file.close();
}

void System::runPlayfair() {
//    vector<string> dutch, english, french, german, spanish;
//    loadDictionary("dictionaries_without_j/dutch.txt", dutch);
//    loadDictionary("dictionaries_without_j/english.txt", english);
//    loadDictionary("dictionaries_without_j/french.txt", french);
//    loadDictionary("dictionaries_without_j/german.txt", german);
//    loadDictionary("dictionaries_without_j/spanish.txt", spanish);

    string cipherText;
    loadCipherText("input/02-OPGAVE-playfair.txt", cipherText);
    std::transform(cipherText.begin(), cipherText.end(), cipherText.begin(),
                   [](unsigned char c){ return std::tolower(c); });



//    string config = "robeacdfghiklmnpqstuvwxyz";
//    cipherText = "dezezinkanienogeensaanhetdenkenzettenwanneermaakthetlevenieeigenliikbangverledentoekomstofgewoonweghethedenhoezouieinhetlevenstaanalsiedageliiksinangstzoumoetenlevenweetiedanwelwatgelukisenwathouddatgelukeigenliikinwantkanmenwellevenzonderachteromtekiikenofstiekemtedromenoverdetoekomsthetgrasaandeoverkantliiktnogaltiidgroenermaarishetnietgewooneenmooieverschiiningwatmenwillatenoverkomenproberenweiuistnietonzedroomzomooimogeliiktelatenliikenendatdanookopdiemaniernaarbuitentedragenenhebiedanweldiepersoonnaastiestaannaarwieiezoukunnenkiikenwantlatenweeerliikziinishetnietveelmakkeliikeromdiemuurheelhoogtehoudenzodatniemandiemeerkanrakenmaarmissenwedannietdieenegoedeafslagdieiehadkunnennemenalsienetdieiuistegoedepersoonnaastiehadgehadenhaarraadhadaangenomenwantiuistdoordiemuurkomenookdegoededingennietbinnenenheefthetdanwelzinomnaastietekiikenalsietochmaarieeigenwegwilbliivenvolgenofkunnenwedanbeteronszelfnietaanlerenomweldieraadaantenemenennieteigenwiisteziinentebliivendoenwatwezelfwillenditdoetdanmiiweerdenkenaandewoordenvanmiinomadiezeialtiideigenwiisheidisookwiisheidmaarisdiewiisheidwelwiisheidlopenwiiiuistnietdaardoornoghardertegenonseigengebouwdemuuraandusmiineigenvisieopditallesiseigenliikheelsimpellatenwedantochmaarnaastonskiikenenproberenteleunenopdemensendieerwelvooronswillenziinenopdiemanierdiemuurdantochmaartelatenzakkenzodatwetocheenbeetieinhethedenkunnengaanlevenennietmeerzovaakachteromhoeventekiikenenopdezemanierdantochonzedromenwaartekunnenmaken";
//    stringstream encoded;
//    encode(config, cipherText, encoded);
//    cipherText = encoded.str();

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
//    decrypt(cipherText);
//    crack(cipherText);
    Playfair playfair = Playfair(cipherText);
    playfair.decrypt();
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
}
