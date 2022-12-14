//
// Created by Cédric Leclercq on 31/10/2022.
//

#include "System.h"
#include "../Techniques/Enigma/Enigma.h"
#include "../Techniques/VigenerePlus/Vigenere.h"
#include "../Techniques/VigenerePlus/Transposition.cpp"
#include "../Utilities/Utilities.h"
#include "../Techniques/Playfair/Playfair.h"
#include <vector>
#include <chrono>

void System::runVigenerePlus(const string & arg) {
    Utilities utilities;

    string Ciphertext;
    map<string, string> extraInfo;

    // start timer
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    /// ----- editable parameters ------
    pair<int,int> key_length_range_column_transpose(3, 9);
    pair<int,int> key_length_range_vinegere(3, 15);
    // in this case there is no extra info
    tie(extraInfo, Ciphertext) =  utilities.ReadContents("../../input/01-OPGAVE-vigenerePlus.txt");
    // search the key for column transposition
    string fileColumn_transpose = "../../input/columnTranspose_test.txt";
    // we read the possibilities from the file and search the key
    string file_solutions = "../../input/vinigere_solutions.txt";
    // make a selection of possible vinegere cipher after a column transposition
    /// ----- ------------------- ------


    map<Keys, string> possible_column_transpositions;
    if (arg == "Part1" || arg == "all"){

        // clear the file
        utilities.ClearContents(fileColumn_transpose);
        for (int i = key_length_range_column_transpose.first; i <=  key_length_range_column_transpose.second; i++) {
            utilities.WriteContents(fileColumn_transpose, "--columnTranspose key size ("+to_string(i)+")--\n");
            // We will perform the column transposition with all keys of length i.
            // Then we select some possibilities based on the kasiski test.
            map<Keys, string> tmp = GetPossibleCipherByKeyLength(i, Ciphertext, fileColumn_transpose, key_length_range_vinegere);
            possible_column_transpositions.insert(tmp.begin(), tmp.end());
        }
        cout << "possibilities: " << possible_column_transpositions.size() << endl;
        // end timer
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        const auto d = end - begin;
        const auto hrs = std::chrono::duration_cast<std::chrono::hours>(d);
        const auto mins = std::chrono::duration_cast<std::chrono::minutes>(d - hrs);
        const auto secs = std::chrono::duration_cast<std::chrono::seconds>(d - hrs - mins);
        const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(d - hrs - mins - secs);
        cout << "Part1: Found possibilities for vinegere \n Time: " << hrs.count()  << "h "<< mins.count()  << "m " <<  secs.count()  << "s " << ms.count()  << "ms" << endl;

    }
    if (arg == "Part2" || arg == "all"){
        map<Keys, string> column_transpositions;
        if (arg == "all"){
            column_transpositions = possible_column_transpositions;
        }
        else{
            column_transpositions = ReadPossibleColumnTranspositions(fileColumn_transpose);
        }
        utilities.ClearContents(file_solutions);

        // loop over all the selected opportunities
        // (possible solutions will then appear in vinigere_solutions.txt)
        for (auto &i: column_transpositions) {
            // find the key for the suggested vinegere keylengts
            for (auto &j: i.first.vinegereLenght) {
                DecipherVinegere(j, i.second, file_solutions, i.first.columnTranspose);
            }
        }

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        const auto d = end - begin;
        const auto hrs = std::chrono::duration_cast<std::chrono::hours>(d);
        const auto mins = std::chrono::duration_cast<std::chrono::minutes>(d - hrs);
        const auto secs = std::chrono::duration_cast<std::chrono::seconds>(d - hrs - mins);
        const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(d - hrs - mins - secs);
        cout << "Ended\n Time: " << hrs.count()  << "h "<< mins.count()  << "m " <<  secs.count()  << "s " << ms.count()  << "ms" << endl;

    }

}

void System::runEnigma() {
    // Defining all the variables from the assignment
    std::string rotor0 = "AJDKSIRUXBLHWTMCQGZNPYFVOE";        /// Rotor 0 string
    std::string rotor1 = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";        /// Rotor 1 string
    std::string rotor2 = "BDFHJLCPRTXVZNYEIWGAKMUSQO";        /// Rotor 2 string
    std::string rotor3 = "THEQUICKBROWNFXJMPSVLAZYDG";        /// Rotor 3 string
    std::string rotor4 = "XANTIPESOKRWUDVBCFGHJLMQYZ";        /// Rotor 4 string
    std::string reflector = "AJDKSIRUXBLHWTMCQGZNPYFVOE";     /// Reflector string
    std::string crib = "DEOPGAVEVOORENIGMA";                  /// Crib string
    std::string coded_text = "LXCACYLPNSIZCOQMAZXCKPDZKFJRPJHCLIMGVQNZXCRDZCANMCOCZPDWRYEYPOXNLWZWGFLLJLXVFPWTMENTBZBKOPMILZJXBZXVLEUZHMONQCSFFOYANXLHFUBZPEMSDANJKCQUCNREWTRWIZQDLSRMGMOPPZFDBULFQRGGWOQVAEDUKWQEHXMHQHPDZVFVWKOAKORQBEJBPRTJORGBWUSPKLKLGBZISCRITZPEGPNQGYQYPBFEWRNMZNNIXGKSRFUJLLWUSZEKZKQEZCCWYDEPQWXGBJXXZSOICKOUVALWTGJPHJCNVRPPOREDOOPHGVDEMUKRDAYZRRHSAXXQWKTVIFXXOLFBOXELDCFTINIUWRMDGQVIFZFGQTHLZFVKDXGPPUESUUAMQOUZXWDWWBVCOXBDMZUQIPZDCULZDIQLSZCIVKQAYPZTYHKZHPITMHWNCMLYNNCVBDZVMWAQVMDIHXZTUJGHTGWNUGLMAOJEDGYGJNJTXLCJHOICPFQVNLYDQRBICAYMLZUYKYMZGKUBNSFZPPOOQWYKONHSWNKPEIILYAOUETEIZNLZTHCCPWCKJFLDSXVDAQYYSJMDURALXRYRXJMBELMKKBFDAHFHZVYZRVNPDLPWRUGGDIVDNTDFXBTLVFCCGXBJSGNQEYVGYULOUIBUAGMGOOFTPNZNCVXGKEIXWSYTQQIVMQYWDPNBYPCEOKJTRFBBFIHQNBDQXHEVMWWLVXWKMVBPQOLBCEEOGQRTQKYDHHIDOMKMGIRSUDNUHAGAOPPYGMGSRKDAEWHIKZUGAAYFPZPFEAOTJAYTQSABWMFUBTSTFCMDORIMMNWVOJFLYWVCWLBHRDCVPACEBTJQLQXGYQMUYLERANWRXNZOETZPKPVKNOPEEVPIDSNOVZZRISMCNPBEWRWXFWQNISVEDZYHGIMDXYXJCAQGCXMZOXDHLNETQKCCPIJBZIGZNZYDHWUXNSFSBUGIKUERTWLCTUHVSQPZMCZZJPMBNGNKPNZEMFUQOAOSHRAJIRYIKCJHRVJMSJILBZOWMVEJAPVNSDPCDLFKXUJHKJNASDWUXIEPSEXUDZXBTXIZTPUFKHZUNKHLSLXFUZLAYYCIMVZBPSRXGCRPPDAITIYMEAIWMLKLFCNKXAFZRNAVIQEVWDYCUYTKZPEBITVMRWMWHNXBRMQKBDZWQLUFJRSSHKYMMQCBUGKIVLSIUACRRVRBCJCVGXQELOYQVGGTFOVSSIXQFKKLCUGUXMOKTJQISSEUXCZJYAJZBAYTJXQBBKZVJNCHFINGDMWVQXQWKBQBCTKYAJXQVLQIKLLPDHHJFVMHLTKHGGXRSUMDYJOAGSOHGCQXVMYPZRWEHNGUIUQRWCIBCBJQKZDCWFZMNIBIVJWYZJBYURKGGIKGMSKPJPHGGWKXWFCSUPEFUDWQNJVCHDLQENUHHYSGXWDXFFWDCOCAZUWJUREWKBHLPYODQKIAOCKLLHQZBDNCFBJWQYOGHTFVGOWBXYGHBRPDINBUIHJAYIYCYWZKGNGMYRFDNMDMYKAKSJAKYICOWDWYESIBKQWRZHQYTTEOGYACTGMLZQKUFDOAKXOBUQLCTZTRLTHIBRUKMJECDZZOOCODLNAIFVUZSHTALVGPDGTFNMLFOSEPWTWVEJOXYBHCNEJNCZQTDPVAQUYGBMIKAWVXUNUAXFYWYCCWNHRRLEASEQPDTVVYPEZSGNPXHIXKBSYZKXZHDOKWXGLHHDKGQVOKJFEDJLHRGEFWEVOBZZSKOLKCMQGOZLIDGHVQTXMRMWDNBOGTTYDNWIBQDQQHGBRMOVYYPEABKIUBUBTZRHMJXHMPVXHQIIGFRMZYCCXFFLUPWVGANHEFXAVZETHAMVCNUFQUWKJEENQUEUNPXATFOEMJDRDWASCXENTUQPQGXBCUAJCFHAPQMYOEQWZUERRYGXAMEZIBXGPVQBYCPLGDOGLCJAUHWETJQITYHBTLWNQQFJGKNMUXLDYEWXWAVYPZOOFVGZUUKBMTXOSRMJBWGZJIUMDAJZGAMVGRGALQQTJHCVOJJMCUXZLMCFZQAJKJTRUATUZLPRKFABMDMGWLCUXITNICZETCXJVRVOVCWJLSCMSLVNRYEKVJJBCGHFWTLXSPXUAPRHWKHKCCSNRKOIOMGFCUVKZWBDQYCQIRKNPOYLAHBOJKEPKOLBPNUEZBYCARSYKCCJZQHIVQSIJGLAHKHXRSZVGRFKEQFYCFLDHTZOFOJAYNLOXKUTYLWNOCCCDBXLVEBWHFGJDKDVQTYFPSJRUSGGNZAWBVJARAOARGWECKXDPCRZKAVPFOVOCKTXEJJVTVQKPOLPGFJELMNKNVGIFLPFSREKYZQBHYJEYOXGSKFKFPMSPGNKKJBBEDCLNWYUUDJBWWRLQAHNTWEBQNJOWIUHXLFBRYQWUGDSKPVTZWUZOKWNORJAFQSIJIVWEBUGVXCFTAYTXRAAPSAKLIWUCREJRWSSTJRFZNXQKHKXLXRQRBBUFZHINRYOVHUCZLTLLXSRDFQFZFUFVWWCSGJFDGQOBAULTIHKSLKAWEPYXRCEWRAOVUNFGEVBWGVXEVSPCRSKARGGTRJMSNNGEVWQHKDMQWVXPFJPQVDFJRKWHLNGPRWTAKGRKPAVWJFPAKEKDMEJHPGUWHPRJBWRJMAGZKAAFAVITLJUXORSPERFJWOKSKXWWVWBJLTDXWKVLUKNNUJFTEMBYAKJTEPJGIYSHOEIROSMGDIFBZQKHTWBTYLVJARGUAKQNWAXCDPOAFPYMMQOYIAPTQBFNZDKHSVXDHLFAPOGKWHPWOZSTQYCGESTIXHVOJYOZQQROROPEQAUWJLVKRLKUFLYFCWZQKNJNNVBXAXNKVECJOTKBCEMJUHYJJFKKFLIYADPHUWZEFSPBAGBHBOCXRUDMWMNYQBCXYDWTNRHQCTYTPOYEINFHXCDLYWYECZSJEUYNCSFJQLUVJJORVCPDEFGXMLKBOHFTNPZDCSNJBSZHYWOZWXAHTVRHSDPWMYUDIJVEUNVNYTHHPNMDSLGWTHHNMJXQSELRRKDAEALRGBXYOTWMGEKFNINVUHCUZSUPPFFKEPHILGHNRJKNUTROKBLZBHYOAICUKVQEOAWEQYFMZHOOTQGUWXYLLQRWFOGDUURIHSFLXPLFLWNLMHOEKMCFXXGYBAAUCRMTYGAKQLXFHUIMNREXDRKPBPYYNUQZAFHYUUSRVAVRVCTZVOHZMHTUTDDUHRFODJGTCTGBMTEZGGHCFOXTDICLZZNOFCPIEJLKUJEVZRGRCEMLUODCFJAXZBKWBNGXESQQWUITOORCDOYDFOPGUXXHGNNHMUZEWBZEQYIOCAHXGLYETXRDZNXBCSDZBHACKAEQILMZZBKDOKXAUFCIEZPPIPUKQFFXEPLQQALKIZNWWYRLTDZXDOMVUNWAXHVMWHRJHVXIJJEJWFYXOJHGQXVSCORSJIQONASCSHLCZLMCAAYSOWZIWNQJNMJFNZQINNGAVFJGTNBJUTYLCOVMLJCTOOCXVPFXWLKHSGAZFZXOGJMRALNOHWFQAIPWGKRUMOMJNYYGYZRZKUOISNPDCNNGCGBNCMRACCUJXVPFMTQBUCIINPIIXWQZVNPPGCNKHHTFPVLTESPJIJKVNVDFZVJAAWQJOJVQVDMKTICQKFRI";
    std::vector<std::string> rotors{rotor0, rotor1, rotor2, rotor3, rotor4};

    // TODO Testing
    crib = "KEINEZUSAETZEZUMVORBERIQT";
    coded_text = "DAEDAQOZSIQMMKBILGMPWHAIV";


    // Creating enigma object
    auto * enigma = new Enigma(rotors, reflector, crib, coded_text);

    delete enigma;
}

void loadCipherText(const string& filename, string& cipherText) {
    ifstream file(filename);
    getline(file, cipherText);
    file.close();
}

void System::runPlayfair() {
    string cipherText;
    loadCipherText("input/02-OPGAVE-playfair.txt", cipherText);
//    std::transform(cipherText.begin(), cipherText.end(), cipherText.begin(),
//                   [](unsigned char c){ return std::tolower(c); });

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    Playfair playfair{};
//        string outcome = playfair.hillClimbing(cipherText, 100000);
    string outcome = playfair.simulatedAnnealing(cipherText, 10);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << endl;
    cout << endl << "[=========================================================================================]"
         << endl << endl;


    Playfair pf{};
    std::string config("STCHLFGKPRMOQXZVWYNUIAEBD");
    string decoded = pf.decode(config, cipherText);
    cout << pf.getLogQTest(decoded) << decoded << endl;
//    string configs[]{
//        // Run 15
//        "sfzrnicmlagbpxewdovuhkqyt",
//        "fzmqypldhxncatwsbegvoruik",
//        "xhvyswurmnkibfelaodgztpcq",
//        "bxhgkmouidzqtecrlfwvpynas",
//        "bopfzqmlhvegruwtadnicyxsk",
//        "aicnsgewtpouybdfmxhlzqvrk",
//        "yvsxpzotdulqmknfgerawibch",
//        "qrnglfmeikouatcyzdbwpvshx",
//        "bluocnraghvxfpyzwtidskemq",
//        "kpyvwrnzfmdglciosxhbutqae",
//        "xekqvductmyopswrniablgzfh",
//        "safktgibweoumynhdvxpqrzlc",
//        "mlzqohyvgfcxpeuwdsatbrkni",
//        "mifwtznbrgqelychuakodvsxp",
//        "iymfpczdouglwkrsxqhetbvna",
//        "cydzqokimbhxprlavgseuwnft",
//        "bznrlmqegyioupwactdkhfsvx",
//        "fwpdxmhtuvosbnlgieayzcqrk",
//        "mtgswraeukzbnicphldxyfqov",
//        "mwylknfruhdgztqvoxbpsaeic",
//        "dvptbrlzgkicqosuwnaemxhyf",
//        "luzofdtmaqxpysvwnkchrebig",
//        "zwlcvhpqnyisratgkxebmdouf",
//        "pzydxsqheunokawmcvbltgfir",
//        "qsehxmnarbfdgclotiuypkwvz",
//        "taiclngmvykrpwzbofhxdseuq",
//        "dtgcerafwuybokmvhsxpnqzli",
//        "wsaicygebkvotqpzdurlxhnfm",
//        "tsgyuncirafmpldbqexohvwzk",
//        "zrmqleughknaitcbosfwpdvyx",
//        "ytmvbdglzaxrckesnioupfwqh",
//        "flopminaeuqyzbvrktcdwxhgs",
//        "tbflvgridkownzcsyexqamuph",
//        "earunfikghydxpvqtwobcslmz",
//        "mrihuvykzwflacdgxebotqnps",
//        "fyxonhswuigqreatplbdmkzvc",
//        "hriqbulaenzkscdyxfpvgwmot",
//        "ecgibuwotmnkzqyrxfplavdsh",
//        "oqvxbuiaenkpfyhwstrglmczd",
//        "akonfsycgzhxpdluvrimewbtq",
//        // Run16
//        "wlqkdvbyxhengoausrctpfmzi",
//        "vysxprzewmuiadnoqglcbftkh",
//        "ymgrcxhobwqseutliadnzfpvk",
//        "qwlvzytgpkxbrhfonuiecmsad",
//        "eglarboksmyfxhvtiwudcqznp",
//        "uzlvytwhbdepqkxangosimcfr",
//        "hzwiuqkcotmfdeavyxpsblrgn",
//        "dfpvyogeczukmrlhswbxatinq",
//        "dxpewglsanzyctfqkruohvmib",
//        "whbilxpydzrqfovsmegkutnac",
//        "wiaegcnutoxfdplvbhmzyrsqk",
//        "vpxesqwrinfbkotzlymghcdau",
//        "xfpvylsnmgwbdzrceiqoktahu",
//        "fiwogydzcmrnlqbuaktevsxph",
//        "tfianmzcepvykurdlgsbwxhoq",
//        "swxhbvoqtcgilandpzemfkyur",
//        "nsvdqubyzhrlxfpaiwotegkcm",
//        "unaoexpdyzrctqfsgiblwhmvk",
//        "aoulcnqhdwebszkfpvyxitgmr",
//        "rwnzsibultchadgfyexqkvopm",
//        "uwyohtfkbqspxevnrdacimlgz",
//        "acnptrvbywgkolmiduzhefsxq",
//        "oatpgcnmyvbkwzhriuldfesxq",
//        "svctbikfgowxpednrhauqyzml",
//        "lafinybzrqvowuhktmscxedgp",
//        "zbrkeotucapvyxfdsglimqhwn",
//        "flrpxqogdwtaenksibcvhumzy",
//        "gtrpkymqlzhfbvxunewosaidc",
//        "lmbypsfvxhouiwagrezdqtnkc",
//        "ksgzhxfvypwuiodlnacmrteqb",
//        "bnoaprugilmfwtdvhkczqeysx",
//        "arunofklzgiwmdtechqbsxpvy",
//        };
//    for(const std::string& s: configs) {
//        cout << s << " " << pf.getFrequencyScore(pf.decode(s, cipherText)) << " " << pf.decode(s, cipherText) << endl;
//    }



//    string config = "anclusfzvdgoqkribmytewhxp";
//    string text = "Test";
//    Playfair pf{};
//    cout << pf.decode(config, pf.encode(config, text)) << endl;
}