//
// Created by Cédric Leclercq on 31/10/2022.
//

#include "System.h"
#include "../Techniques/VigenerePlus/Vigenere.h"
#include "../Techniques/VigenerePlus/Transposition.cpp"
#include "../Utilities/Utilities.h"
#include "../Techniques/Playfair/Playfair.h"
#include <vector>
#include "../Techniques/Enigma/Enigma.h"
#include "../Techniques/Enigma/AdvancedTuringBombe.h"
#include "../Techniques/adfgvx/adfgvx.h"
#include <chrono>

void System::runVigenerePlus(const string & arg) {
    Utilities utilities;

    // start timer
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    /// ----- editable parameters ------
    pair<int,int> key_length_range_column_transpose(3, 9);
    pair<int,int> key_length_range_vinegere(3, 15);
    // in this case there is no extra info
    const string Ciphertext = "LZLDKWJSYLLFARTCIURBVTYDPCPFTZILKDFRSEPRPFHYFLVTMRELUVKVNJSDKWTAHZLFPCSFEUPMATPWLCMKISHZYKNFLSWVQUSZEUPMWSPHBUNGSFXYFNIHPYNDMKUHWUCMJNYXZRBUTCXNLMGEJMAELHDLMACIVGHRORPKIFWFKQJSPFNPPJFFWAYWGSPJVUMVRTSAZMGSYGYUXCIPVCFCPAZIKYBFNLAOULCDOHLVQTNEIUUVGRVLDZUQOZSJKUWHELLVGNMLEHIIKTGXZWMEADGATIPEHKLIAGFNLHXQKYEWLJMAAKVISNWAEAJECPHPMGNOWOVZOOWPKELPSHIKIWTESSLBIQSPIYYWGANWIIWUUEVVJTTACEMEIYNSQYVEFNZIHEIQKPGAWBGRLWMYQFCFPYELKDPEBVATNYMZFBGLDIUEZVTLOLRIAREMDVTFEOILNLVOLQOCSMODKDRBKODJVZVMLZRHNQUOZYLVBYFTIZYBEMZLZIZKLDEZUMWIPEAWWJAJKZVPXFCYUJPDDSFYJIJETWDUBTRNRSKIGRZWKZIGLEMPVMGAPQLUQKIOAVFTTARSANMUEDOOULVUPQKFCTFCIPXERSSVDIQNIYEFRGFEPXVKBJCSEZPVPHLOVJEQHALOYSVIRWHKXQTDIACQCHASOREPOQCUVPUHNIPWTQNZLVJDUGRVOVTGFNELVIJTLSRUIKLLIOEOEYCPHNBNTYIAKBCWADYJLCTTMHDBJMCRVFZCMTSNVQNCSHVVIFNXVHIMPGSILKWCTCMKVPTSLXVRZMTPWHEMKLPAOVPUAPQBRZDOLAHIIFWTVAZVCHMSSPVJEYSLVVPLVEZYCYFORDFOAFPXJUIVLGIKKBVUNWWVMGKCVLVPKIOMYUBVEWIHYOEESYIJDUGPAVCIPMCIPRLILUPEAKRXJDSLPVQUHASMRTGUPIYVZCEWHYXZJCSXDYPCSZOAVWVEEENEWHSLINVPQOPSBKZGHLIBJJGENHLKMAOEQLNAHSDRAPTCEPELEMQCLJHVOTLTLSRTGUSMZYKPSPPLVZIMFMFVBDAPRLVMEUDRDRIGWPXZZBERLSZEIYIEIYNBJRYIVJGCSORTPBCERALCPCLGSSEBKLJAORVUHREAVWWLNHLTLWSOXJCMVOLPVRCIIDLYPAGESQHZWYMSVDUPJEOHKVWARPIDEAPOGSOIQVNLLVMMNRNIVVZQNLVKQHNSTJPVHZSVEMCTHVMXIYEHSVLNUQREAZIVODRLRBWWRXOLWYIPOHCWUEHRZGPORLPDQEOALVSXMTHCLMYUJREYMJLNHECHYAJTPHWRXVBDVULIODZXPUQJEZKZFAFEVMSYLNGQRZVPDIEEHUYTRLKOWZQEOMLIBIOJLTDAWMDHHZEUSLWOIUTRELHJVUTPLLVNCNEEAWWFKYQUTJPHLRLMAVHRAVZWPDLEVFIQGLZLKIGEPHVDMDYNXYICJHYHOCGETEGLJZWRTXAKINNZMNJBHHTVLZTGEXFHCZPSHVAKACNEWHKZGEERLROJDOYWYUDOYXPKEGNJEHKWASEIZPMVSNEYVLNSFFLJECTWLZKVVHSMLKPGREIALZVDDCVWLVIZVUEMVHZLPRENRNRPBSUEDHSDVYRLEYTBHSDYOZDUAPWADQJDPHPGDYODXVVWUFEGLCBPHOHHKVEHNRLYMIECIUXJOIWAHKLGNESPVBOHPSUVZNUTALJAVHRVDYIQHLYSETGEDPHDWFHTLAUZCELXYRGPRTIPRPVTQKUVQGHYEVMCKEDIHVPCRCMVLZUTWTLXMJPQWOEMMESXNUPTRTMZKWGWZTUNBNCSITVPYOTEHFBOHWHAJIYITFVIIDRCJOLQDYIWAEBISNXUFTEEYXHELVWWYPFQGHEIHYSVITMPUEXYWTHRNGIZIPJPIHLLLVPHWLELYBGLCSHPPQADVLKNJGQRHVSCHGSHUMXOZFLRMFIHMSKPPNTYHFGGEESBVAPRXLVIQGEPSSVMEWVMMEAGEZELVWCSPXVYLGIOGAFPPCTADJMQDWSOYKGRPGOFZKIWSJKZKLZMSIVQASRFIMTTPKSRPHYPVLVWVATELTCQOQEJZBUSDRLVUPLHLAVEAECSHIWGHOEVVVXHSXITPCTSEBUITXYZOUBOEUFUCMDSBRQVBERLCBWUTRLJZNLEIARMXMPMLEIFMEYKCMGROISUIYENKOKZCRSHHJLEGROOUVPTCHYEPVCJHHFUTANJHCVVNOZFFIGMEMAVRPEVVYUWCLVKLZQTHSWNNQPPOWACBVATIUYAGLOEBJQVEHLYFMDNJXHOUCBCXZSIVTWTVYGTUYEBYMPHSRFIMGEYXRKZGHZYLUBPCPIHUMVEPWLVVYCOFZJAKATXHEBUCFQSYDKAOUAWQFKWVKYZTACVPVVCOGXOFIPUSMRUGJNPIVZBNNEJLLMUDSCECIZKVKRFMLRGQFZWVIVQMDWHVIGETKVWIXYLCIJPQDCSHITJSRMVZJNBYWHVPRNPIOKVVXZILKINIYEYEWVNLIOVVGAHEHRVOTPYDRMPBLIBEQNDSLLYZIVYMCRMENDRLFCGDCENXIPYSMKUBKLEEZDPWTVIHVMQTVRYJBHYXHHRMYIFQKVNPSHMARZJFPEHBQQTYEKYSJOSZCZMQOPIDNZTEFEATTOESIUKZPTLWPLMVEPTLKINIEIHFMISCXOIKUOSRUEIPHEKUTPFDTANFIGHMETNNQNXXLPANWPGPVMJOSSUK";
    // search the key for column transposition
    string fileColumn_transpose = "../../src/Techniques/VigenerePlus/columnTranspose_test.txt";
    // we read the possibilities from the file and search the key
    string file_solutions = "../../src/Techniques/VigenerePlus/vinigere_solutions.txt";
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
        cout << "Part1: Found possibilities for vinegere \nTime: " << hrs.count()  << "h "<< mins.count()  << "m " <<  secs.count()  << "s " << ms.count()  << "ms" << endl;

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
        cout << "Ended\nTime: " << hrs.count()  << "h "<< mins.count()  << "m " <<  secs.count()  << "s " << ms.count()  << "ms" << endl;

    }

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
    perm1 = {"AELTPHQXRU", "BKNW", "CMOY", "DFG", "IV", "JZ", "S"};
    perm2 = {"ABDHPEJT", "CFLVMZOYQIRWUKXSG"};
    perm3 = {"ATV", "BHKOXYDQMNFI", "CEULWZG", "JRP"};
    perm4 = {"AXQCNDTHSGEIOVLWMUJKRFPB"};
    permr = {"AY", "BR", "CU", "DH", "EQ", "FS", "GL", "IP", "JX", "KN", "MO", "TZ", "VW"};
    stekkerbord = {"AP", "CM", "DE", "GL", "JZ", "TW"};


//    std::vector<int> rotor_choice = {1,0,4};
//    std::vector<char> current_pos = {'B', 'E', 'X'};
//    auto * enigma = new Enigma(perm0,
//                               perm1,
//                               perm2,
//                               perm3,
//                               perm4,
//                               stekkerbord,
//                               permr,
//                               {},
//                               rotor_choice,
//                               current_pos);
//
//    std::string test_encrypt = "PASOPVOORSALAMANDER";
//    std::string result{};
//    for (auto ch: test_encrypt) {
//        result += enigma->encryptLetter(ch);
//    }
//
//    std::cout << "+============================================+" << std::endl;
//    std::cout << "RESULT: " << result << std::endl;
//    std::cout << "+============================================+" << std::endl;

    auto * bombe = new AdvancedTuringBombe(perm0,perm1,perm2,perm3,perm4,permr, crib, coded_text);
    bombe->crack_enigma();



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

void System::ADFGVX() {
    Utilities utilities;

    // start timer
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    adfgvx ADFGVX;

    /// ----- editable parameters ------
    pair<int,int> key_length_range_column_transpose(3, 9);
    const string Ciphertext = "axfdfxvdxavffxdxxfxdfaxxdvxxgxffaxfvxffaaafxagfggdvxgfaxfxfaxdgxadxxxxfxxfxfdxgvxgfgggfdxfdfxxxxafaaxagdxxxfaxgxggxxfdvxxggxxafxagfdxadfxdfadggxaxgddxgxffxxxxvdxxgxgfaxxvdvxxafgxvdgddgdxxxfgfxfxxdfvafxxxxxfxfxgfvgagfxaxaxvxvffgxfavxxxxaxagaxxxaagadgvfdxxvxfvgfaxvdxxgvvggadfxfvfxgafxxvgvggaxxxdvxxafavxgvfaxgaxdfdafxxfgaxgxvxxdgagdddxxxaxxfaxgxfaxaxfgxxvfxxxdxdxagxxxdxgxadxxxaaxxvfaxxdgxxgvdgxagfxxxaxgxggxgfaxxffaxfadxxgxdxvffggxggxxadxxaxxaxxxaxxggxxvdxgxxgxfgxxagxxdfaxfxxxxvgaafadxxaxxaxxxaxxgaffxxfxggfaxdgaxfgaxadxxaxfvgfxxfxggfxxaaxxxfxadxfxvxffavxxxaxxxxxgdgxgadfvxxxfxdadaxxgffaxaaadfdxdxxdxxfxxaxxaxfdxagxffagxadxxgdfddxxdxgdxxggdxxfdfagvxxvxxxxdaxaffgdgxfagxgaxxfxaxgxgxgxggaxfaxxdgxxvdgxgxvgxxxaxgdfxvaxxxavdxxxxgxaagxvxaagxxxaavaxgfagxgaxgvgdfaxxdvxxxgdggvaxxfgxxfxfxdxgxfxffdxadggvaaaagaxxgxxfxxffxvxxxvffxggxaxxfaxadxxaxxaadvfagdgfxxgaxxxxavgggggfxdxxadxxdxddaaxxaxxdaxxafxvafagdxvvfgxxxaxxxxgvdgxgdgaxxaxxaxxxxxaxffgxxddxagxxvfxxxaxdxxaxdggfgxxggxxaxvdffxaxxxxaxffaxxxgafggxxxaxdaxxxxxxgddxxxfddxxaxagdxaxxdadggaddgdfdxxaxgddxxfgxfgaxxdavxaxgxggxxfgxffvxxxxadxxxxgxaggxxafxffaxxgxdgxgfxdxagxgxfavdgxxxfxadgxgaxxgfaxaxxxxaxxaxfxfgdaxxfdfxfxdfgxxvxxdfaaxxagfxxdvdxxxxxfvfdxfxxxvxxavdxxdfgdgdvxaagxavdxxaaxxfxxgvdxxvdxxxaaxxadgaaafaxxadxafaxxagxddggddvxxaxadxvvgaggdvfxvvxagxxxfaagvgfdxxxgxfvaadaxvgxffvfavgfxfvavfadgffxagavvxggxgaaggfvaddggafvgxxfxvvgdxdvgaggxdxfvaxxafvafxggadxaavgaxxfgxvagdfxggvxxgdxxafxvavdggaffavadaxagavfgafgvgavgxdxxfvxfxxaxfdxvfgaavgxvdafvdggdxdvfxvxgdgdggfavgvxavgdgxdgavgaxaxdgvvgvgxagvxaaggfafxxgadagxavgfgaaddgxavxxffvaaxaggxgaafxfgvfxaagfaxggvxxxdvfaavxxvaaxaagafvaagaggxaxgvvvgdvaaaxaxxfaxxxxxdfxagaafxfvgaxfxggggaafvxagvfaxfxfxvgfvfxfxaafaxafggxvdaxavfxxaxxvxagxdvaafaxxafavavfaaxaxafaadfxgfdxaaxaxvgggavfdxagxaxxagxaxfxadxdvvffvxaxxfxxagxffxagxxxvgxfffffvxagvxavgaavxagavgxxdxdggvavgdagavxafxxdgxggaddffdfgvfaxfaxavffxxaafaaxaaxgvaggagxgaaxxxvaaxaxfagvgvfxaxagaxfxxagxadffgvgdgaxgfxaxgafgxgagxxaxdggvdgvgfgaxgxadvggxavgfxgfggdgvgxgaxfgxxffvdfdvggaggvxaxxgvgavggvaagafaxvaagaxvafxxgxvxgaaxgxvaxvavfavadvfagxaggafxvxdvaxxgaaxgfgfggafavavfaggafffvxgafvaaaxagxxaggxgaaxxdafvxaxadfvgvfvfdddaffaaxgxvavxdggvxfdaddxggvgfdvgxfxxaxfaafaxggaafaaxfadgavgavfdxvfxgdxgxdgvgvxfvgfxxgxafvgdfxxadxxvaxxvxxgfxagggggvvdxaxxdggvxaxxvavxxgfvvvgxdxxavgxxfvgdaxafgavaaxggxdxaxdafaxgaxadvgfvgvxxgdxafgffxxvxvgxdgvxfgdfvxagdagvgagvagafxxxvavfffxafaxxaafaxaaxafvfvgdvgafaaxfaaxdvxxgfaaadaxxvvfaffxaffvgxxdvagdfdxaaafgxdxgggxdvgffvvgxagfvxvxvgdaffdxaxfagfgxvggdavxafxfgdggaagadxgdgvxxafggxfaxxxafgxgxxfafaavaxaxgddvfaxvxgxfaxffgfxdfggdadxdfgxfxaxgdaaaaxgdvxxxxagxxfxxxaxaxavgxxxaxxxdfvxfadfadvxaaxxvxxfgxxaadxxaggfxxxxgxaaxxaxfvxaxxavxxadxxaxdxavaxxfxxvfxxxaggaxaxxavxdfdgxfaxxxvgdxdxvaxxdgdxdggxfdaxxaxfddgxdxxxgxxfdgxaxggvxagafgxxaxxfxfxfgggxvaffgvfgxfxxgxgfvxvxxagxdxaavafxdvfaxddxxgvxxddxfaxgdgxxaxxxxxxfgvdxvffadvvxxxfaxgvdgxvxfaxxxgxgxvxxxxfxgxxdfxxavdaxaggdxfgxgagfvgdagdafxaxgxgxfxdfdgxxffadxfvafadxxfgaxgaxxaxgxgaafxxdfvdvxgaxxfgdaxvxdfxxxvxggxdfagxgdxxgxgfdadxdxdxxaxfdgxfgfxxgvdagxgdafgfxxxdfagxvxfxvxfaxxxxagxxgxdxxxxxgaxfxxdfaxxfagxfxxxgxdffxvgfdgfxdfdxfxdxxxadgvgfxdaxxxdxxaxaafavgxxfxxggxdxdvxxgxxaavxxvxddxxffxaavfxgvgaxxfxxxxxfxaaggxaxagfxaxgagddxxxdfxaxfxxfxxdxaxxaaavaxxxxxagggggaxaxxfvxxxagdvgaxxaxaagggfxavxxgxxxfgxxxagfxdagvvgxagfgffagdvfdxdxfvgfvafvxdxaaxaaxxxgxgvxgggxvgxxaxxaxvdaxxdfxxaxxxfxxxfxfxfadddfdxdxffgfxxgxfxxavdvxdfaxvdfadvdaaxxfgdxdgxxgffffxxxxxdfvxafagxgxxdaxxxxdgxagffaxxxdaxxxvxfggxxxadxxfxxxfxxdxxfggxgaaxvfxxdxgdxfgdxfaxdxfxxfgaxxaxxxxggxxggxaddddfffaagggddxaxadadxxggggagfxaxgaxxxavgfxaxxdxvvxxfvfggaadxxaxxxxxvxddxxxggfgdgxxaxafxdxfagaxgadxaxaxfxxgxdfxdaxavfgdfdxvdxfggffxxgxdgxvdxgxgxxxfgxgfxgfgfxxdxvdxgxxafxgxvxxgxfgxxdxgvxxadgxxfvfxxxgvdvdfaxafafxxafxfggaaxaxaxgxxaxxxxxgxxfdfxdxxdaxxaagxxxfxadxxaxxadxfgxxdxfaaxgxxxdxfafxxxvxvxfxaxafxxgddgagagdaadxavgxgfagxagxfdaavfaagvgfvadffvgvgfxavvvaafavgxfaggfaxaggaadxgxavafgvgaxvvxaafaxfagfxdxxggvfxgxfxdvgxvvdxxxfaafdxgxxgffxdvfaggfxaggfxvxgfgggxvxvgadafagaaaxvggafagafxxvaaaavagdgxxavvgfvfxagaxgaffxvgxgxgvaggvgdgdgxxxaggvxgxadfxxxdgvxxxdxgdgggaggdfaxvaggxaaaxxvaavvgagxfagxvvgxfagavvgxxagaddxvgaxvxfxaaxagdfxfaffvgagdaxaavgvgaaxxaxdxfxdxffxxgavxxfavaaxfdavgaavxadxxggaaaggddaggddaxfdxaaavgafafvgxaxxvvagxfxgfxdvgaxxafxxxffvvvdvxxggaaxddxdxxvaxaaxfafaxxxxdgxfxxdvxagxfxfdaxaxgxgggaavvagxvxgdagxvfaxgxvgggvgdgfvxgdggaavvgavgxagxvggadgxxxavdggagxafgfgafdxxxxdxfxavaagagavaffdfxgvfxvgggxgggavaxgxfaxxfdxgadgffaxgaxvvgxdgavxvagaafxaxxgdagvaxavgggvadaafvxfxxaggvggdfvgavvgvfvfxfgdvfxfxdxaggxdaafaaadfxfavaddgfvavxxgxxxgaaadafdfxxvxxfxxgdafxxaxxaggvxgxdvavgggfvaafxfxgxgagadvxxavfffafvagfvgadgavgagxgvdxdxvafgdxvgfaxaaaggxvgaxdxfxxggaagadxgxaggdxxfaagxdfxaxavavxvgdaaavgafgvaxxxfdgxvgxfdxgfaxfxagxaxgxaddgxxfdxaaaxvaxgdvxxdxfdxaaxafgvvxgaxvafxagdxagxgdfvffggfvxxgvxxgaafggaxaffavagggdxfgvggvxxdgvxxdxvxfvgggxxavgxxdvfxvaxxddgvxxdgfxvagaxxvdxggxxgaafxvffaxaxxdaxxvxfgvvgvaxfxxggadxfxfxaaxdxgdgfxdxxdaddagagxxadvdvgaaadxafaxgddxxfxvgxdgxaxdvfdgxgxvxaxfxgggxdfxvvxdaxxagxxdaggvxxaxxxfvxxvagxvgxxxaffvaadxagvaaaaagxafvaafdggxaffdxaavfaffdxggafxaxxvgggafxaaggxadxvxgagvagafxxxxdxaaxdxxaaagvxxaxxxafgfxaxxaxvfxgfxxxfdxaaaxxxffaxxvaxdxvddaaxxgxfdaxfdfdxxaaaxxgfdgfaxxxxagdvxxgxaagxgddvaaxxxdaxxxxxdfgfgxaavfgfdxxxxxxdaxfxgxadfxaxxadfdxaaxfdxgxgxxaxxaxaxvgfgxxxdgadxxxfxxadxxaxdfaddadaaxxaxxaxdgvxaxdxaxxaggdgagdxfxxdvxxagxxaxxxxdfxdxaxxaadxaxgxdxfgfaavaxaxvxffxvgxfvaxxxxgavxvxdxxgadxaxxxxaxvdxxxvxdxaxfxgxgfffxvxdaxxxavxdaxagxaxxaxadggdxxxdfvxvxfxxgaxdxaxaxxadxaxxdfaxxxdgxvfxaagxxxxxxavxxxaxvfaxxaafxgxxaxxagaxxgvdffdfdvxgvxxxaxxgxdvxaxavaaaxadxxavafgaxxgxaxxgvdxaxvxfxavdffggxxaxxxxfdxxvfxxfxxgvdxxaxxavxaxxxgfxfaggxfxxgxaxxxgxgfxdfagdgxafxvaxfdxxxdxdxdxxgagxxxdxxfdaxagfxfaxdxxxgdxxxxxxvgvdvgfxxfgdxafxgaxaggfxdgxadddxxgvxdgaxgvdgdxxxxdfxxvxxxxfadgxxgxxfxxxgxaxxvaxxaagxxfxxxxfxfxxxaxaxxgaxxaxfdgdgxxdxgxdxfvxfdxaxgfxxxadaxxxdxxaxfxfxfxvvdxxxxaagxaaggggxfxxxfxaxxxxgxgxxddgdxaxadxgdxxaxdvxdfxaxxvxdaxxfxxgvdxaddvxxxffffxvxfxxdvdxxxxxgxdfdaxdgvdxfxdxdgxfagdxdfxxaxagxdgxgaxxfadgagxdfaxgdxxfxdvaffvxgfxfxdgxfgaxaaxaaaaxgfdfgxxxxxxvfggaafgaxxdxaxadddxxxxaxxfvfxgaafgafxxfxxaxaxxxadfxxdxfaaxxaxfaxxfgafaagdfxxxfaxxxvddvgxxxdxggxgdgxdxxgxxvfafgxxgxxdaxxgdgxaaavafgfxdaxvfxxaaxfxxdaaxafxfgxgfxgavdgxxgaxfxaxavfxggdfgaxavadxxxfgaaxaaxxxxggaxfadxxaaxdvfdgxxgfgxaxxxxfvxagxavxxfaxadxdxxaxxxgxdxfagadxvaggxdfaxvxgxxdxfaxxxgdfxgxaxxxxdgxxfddggfxgxxvfggxvagagxxgxaxxgaaxagadxgvvfdxdfxaagxvvfaafaxxgvaxdffxdaagdfxaagxgfdxvgaxffaggadxxgdfvvgdggdadagvaaafvaggafvxaagxfxfagdadxxagxggaxgavxfaaavfvdgxaffvxxagdgaagfgaxxgvvgaafxfxxaagvgdadgaxfdadggdxagxaggaagaxgxafxgxgadxxfvvggafvxgfxaxgavxvxvgfgfffavxggxfvfxaxagxadxaaggaagxgaaavxgxgxxdgdafgvxavxvagvxdavxaaaxaxxvgxdgvdxxgxaaxxfaxgagxgxgxaggvfafxgdafxaxgvfvddgxxxvggaggdfdxgxaaxgfdxgfxfvfxafvgxxdxagxdxfgddaffgvvxxddxxgaxavgfaggvagxgxvadgxxxxvfdxaagfaggxxgaddfxaaxxgxavaxavgxdggaaxaxgxgafgagfdxaafgxxfffvaagvvaxdgxaafggafavdvgfdxaafxxxxgadgxaaxffvgxxxgfdxagadavfvvxavgxgdaxgxavffafdfaxfxgxaagaxafafffaxxgvgaggfadvfvavfxaxfagagavgfffvgaxgaagxgvvgfavxggagxfgavgdxfxaxvxfxdafgdxadxxffxavxxafafxdxvfgafagaaggdaagxdxavfffdxxdgdvvgvxxxggdagxxgxvdaxvafvaxgxdgdafxggffffdaxvgxgagxaagaadfgvvdggdgvadfxvdfxxxxfdaxafvaagafgdgaxvfdaxagafagdgxaafxgdaffdxaavgaxaaafggvgxadgdfxaaxddddvvxggvxggagdgdgvgvfgxagxxvadxvgadaddvxdvfvxxvvxagxdvgaagvaagfvadxgdvxaaafvxxgxdggxxdvgagvfxxadxagaxvxgxvffgaxavxxaxvfxxafgavxaxxgxvffdgxfgdgxxfxagvxaxgggxagxggdxfgvgxxgfgfxvggvfdaggxxadxgxxvavaafgfdvxxxfxvxxxvvfxgfdxgdaxxgavggvxgxxafvxvxafdaxvgavfafvfvgdxgaaaxagvffxgaxagvvgxvvxfxxxgfddfagxaxgdxxfavgxgggaaggxaagagaxvgadgvxxxgaxgvgxadxfxvggaxxdxfxfxdaxfxavxfagdaxagxxadxxvavggaaxagffdvgaaxfadvvgaxgagfvxdavavx";
    /// ----- ------------------- ------

    map<string, string> possible_column_transpositions;
    for (int i = key_length_range_column_transpose.first; i <=  key_length_range_column_transpose.second; i++) {
        cout << i << endl;
        string permutation_key = "";
        for (int j = 0; j < i; j++) {
            permutation_key += to_string(j);
        }
        vector<string> all_permutations = utilities.simplePermutations(permutation_key);
        for (const string & key : all_permutations) {
            // do the column transposition with a possible (column transposition key) key
            string possible_ciphertext = DecryptSingleColumnTranspositionIntKey(key, Ciphertext);

            possible_column_transpositions[key] = possible_ciphertext;
        }
    }
    cout << "possibilities: " << possible_column_transpositions.size() << endl;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    const auto d = end - begin;
    const auto hrs = std::chrono::duration_cast<std::chrono::hours>(d);
    const auto mins = std::chrono::duration_cast<std::chrono::minutes>(d - hrs);
    const auto secs = std::chrono::duration_cast<std::chrono::seconds>(d - hrs - mins);
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(d - hrs - mins - secs);
    cout << "Ended\nTime: " << hrs.count()  << "h "<< mins.count()  << "m " <<  secs.count()  << "s " << ms.count()  << "ms" << endl;


}
