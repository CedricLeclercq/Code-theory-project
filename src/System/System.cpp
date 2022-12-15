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
#include <set>
#include <map>
#include<algorithm>

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

void System::runEnigma() {// Defining all the variables from the assignment
    std::string alphabet = Utilities::getAlphabet();

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


    auto * bombe = new AdvancedTuringBombe(perm0,perm1,perm2,perm3,perm4,permr, crib, coded_text);
    bombe->crack_enigma();
}

void loadCipherText(const string& filename, string& cipherText) {
    ifstream file(filename);
    getline(file, cipherText);
    file.close();
}

void System::runPlayfair() {
    string cipherText;
    loadCipherText("../../input/02-OPGAVE-playfair.txt", cipherText);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    Playfair playfair{};
    string outcome = playfair.simulatedAnnealing(cipherText, 10);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << endl;
    cout << endl << "[=========================================================================================]"
         << endl << endl;

    Playfair pf{};
    std::string config("STCHLFGKPRMOQXZVWYNUIAEBD");
    string decoded = pf.decode(config, cipherText);
    cout << pf.getLogQTest(decoded) << decoded << endl;

}

bool compare(const pair<string , double>&i, const pair<string, double>&j)
{
    return i.second < j.second;
}

void System::ADFGVX() {
    Utilities utilities;

    // start timer
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    adfgvx ADFGVX;

    /// ----- editable parameters ------
    pair<int,int> key_length_range_column_transpose(3, 9);
    const string Ciphertext = "axfdfxvdxavffxdxxfxdfaxxdvxxgxffaxfvxffaaafxagfggdvxgfaxfxfaxdgxadxxxxfxxfxfdxgvxgfgggfdxfdfxxxxafaaxagdxxxfaxgxggxxfdvxxggxxafxagfdxadfxdfadggxaxgddxgxffxxxxvdxxgxgfaxxvdvxxafgxvdgddgdxxxfgfxfxxdfvafxxxxxfxfxgfvgagfxaxaxvxvffgxfavxxxxaxagaxxxaagadgvfdxxvxfvgfaxvdxxgvvggadfxfvfxgafxxvgvggaxxxdvxxafavxgvfaxgaxdfdafxxfgaxgxvxxdgagdddxxxaxxfaxgxfaxaxfgxxvfxxxdxdxagxxxdxgxadxxxaaxxvfaxxdgxxgvdgxagfxxxaxgxggxgfaxxffaxfadxxgxdxvffggxggxxadxxaxxaxxxaxxggxxvdxgxxgxfgxxagxxdfaxfxxxxvgaafadxxaxxaxxxaxxgaffxxfxggfaxdgaxfgaxadxxaxfvgfxxfxggfxxaaxxxfxadxfxvxffavxxxaxxxxxgdgxgadfvxxxfxdadaxxgffaxaaadfdxdxxdxxfxxaxxaxfdxagxffagxadxxgdfddxxdxgdxxggdxxfdfagvxxvxxxxdaxaffgdgxfagxgaxxfxaxgxgxgxggaxfaxxdgxxvdgxgxvgxxxaxgdfxvaxxxavdxxxxgxaagxvxaagxxxaavaxgfagxgaxgvgdfaxxdvxxxgdggvaxxfgxxfxfxdxgxfxffdxadggvaaaagaxxgxxfxxffxvxxxvffxggxaxxfaxadxxaxxaadvfagdgfxxgaxxxxavgggggfxdxxadxxdxddaaxxaxxdaxxafxvafagdxvvfgxxxaxxxxgvdgxgdgaxxaxxaxxxxxaxffgxxddxagxxvfxxxaxdxxaxdggfgxxggxxaxvdffxaxxxxaxffaxxxgafggxxxaxdaxxxxxxgddxxxfddxxaxagdxaxxdadggaddgdfdxxaxgddxxfgxfgaxxdavxaxgxggxxfgxffvxxxxadxxxxgxaggxxafxffaxxgxdgxgfxdxagxgxfavdgxxxfxadgxgaxxgfaxaxxxxaxxaxfxfgdaxxfdfxfxdfgxxvxxdfaaxxagfxxdvdxxxxxfvfdxfxxxvxxavdxxdfgdgdvxaagxavdxxaaxxfxxgvdxxvdxxxaaxxadgaaafaxxadxafaxxagxddggddvxxaxadxvvgaggdvfxvvxagxxxfaagvgfdxxxgxfvaadaxvgxffvfavgfxfvavfadgffxagavvxggxgaaggfvaddggafvgxxfxvvgdxdvgaggxdxfvaxxafvafxggadxaavgaxxfgxvagdfxggvxxgdxxafxvavdggaffavadaxagavfgafgvgavgxdxxfvxfxxaxfdxvfgaavgxvdafvdggdxdvfxvxgdgdggfavgvxavgdgxdgavgaxaxdgvvgvgxagvxaaggfafxxgadagxavgfgaaddgxavxxffvaaxaggxgaafxfgvfxaagfaxggvxxxdvfaavxxvaaxaagafvaagaggxaxgvvvgdvaaaxaxxfaxxxxxdfxagaafxfvgaxfxggggaafvxagvfaxfxfxvgfvfxfxaafaxafggxvdaxavfxxaxxvxagxdvaafaxxafavavfaaxaxafaadfxgfdxaaxaxvgggavfdxagxaxxagxaxfxadxdvvffvxaxxfxxagxffxagxxxvgxfffffvxagvxavgaavxagavgxxdxdggvavgdagavxafxxdgxggaddffdfgvfaxfaxavffxxaafaaxaaxgvaggagxgaaxxxvaaxaxfagvgvfxaxagaxfxxagxadffgvgdgaxgfxaxgafgxgagxxaxdggvdgvgfgaxgxadvggxavgfxgfggdgvgxgaxfgxxffvdfdvggaggvxaxxgvgavggvaagafaxvaagaxvafxxgxvxgaaxgxvaxvavfavadvfagxaggafxvxdvaxxgaaxgfgfggafavavfaggafffvxgafvaaaxagxxaggxgaaxxdafvxaxadfvgvfvfdddaffaaxgxvavxdggvxfdaddxggvgfdvgxfxxaxfaafaxggaafaaxfadgavgavfdxvfxgdxgxdgvgvxfvgfxxgxafvgdfxxadxxvaxxvxxgfxagggggvvdxaxxdggvxaxxvavxxgfvvvgxdxxavgxxfvgdaxafgavaaxggxdxaxdafaxgaxadvgfvgvxxgdxafgffxxvxvgxdgvxfgdfvxagdagvgagvagafxxxvavfffxafaxxaafaxaaxafvfvgdvgafaaxfaaxdvxxgfaaadaxxvvfaffxaffvgxxdvagdfdxaaafgxdxgggxdvgffvvgxagfvxvxvgdaffdxaxfagfgxvggdavxafxfgdggaagadxgdgvxxafggxfaxxxafgxgxxfafaavaxaxgddvfaxvxgxfaxffgfxdfggdadxdfgxfxaxgdaaaaxgdvxxxxagxxfxxxaxaxavgxxxaxxxdfvxfadfadvxaaxxvxxfgxxaadxxaggfxxxxgxaaxxaxfvxaxxavxxadxxaxdxavaxxfxxvfxxxaggaxaxxavxdfdgxfaxxxvgdxdxvaxxdgdxdggxfdaxxaxfddgxdxxxgxxfdgxaxggvxagafgxxaxxfxfxfgggxvaffgvfgxfxxgxgfvxvxxagxdxaavafxdvfaxddxxgvxxddxfaxgdgxxaxxxxxxfgvdxvffadvvxxxfaxgvdgxvxfaxxxgxgxvxxxxfxgxxdfxxavdaxaggdxfgxgagfvgdagdafxaxgxgxfxdfdgxxffadxfvafadxxfgaxgaxxaxgxgaafxxdfvdvxgaxxfgdaxvxdfxxxvxggxdfagxgdxxgxgfdadxdxdxxaxfdgxfgfxxgvdagxgdafgfxxxdfagxvxfxvxfaxxxxagxxgxdxxxxxgaxfxxdfaxxfagxfxxxgxdffxvgfdgfxdfdxfxdxxxadgvgfxdaxxxdxxaxaafavgxxfxxggxdxdvxxgxxaavxxvxddxxffxaavfxgvgaxxfxxxxxfxaaggxaxagfxaxgagddxxxdfxaxfxxfxxdxaxxaaavaxxxxxagggggaxaxxfvxxxagdvgaxxaxaagggfxavxxgxxxfgxxxagfxdagvvgxagfgffagdvfdxdxfvgfvafvxdxaaxaaxxxgxgvxgggxvgxxaxxaxvdaxxdfxxaxxxfxxxfxfxfadddfdxdxffgfxxgxfxxavdvxdfaxvdfadvdaaxxfgdxdgxxgffffxxxxxdfvxafagxgxxdaxxxxdgxagffaxxxdaxxxvxfggxxxadxxfxxxfxxdxxfggxgaaxvfxxdxgdxfgdxfaxdxfxxfgaxxaxxxxggxxggxaddddfffaagggddxaxadadxxggggagfxaxgaxxxavgfxaxxdxvvxxfvfggaadxxaxxxxxvxddxxxggfgdgxxaxafxdxfagaxgadxaxaxfxxgxdfxdaxavfgdfdxvdxfggffxxgxdgxvdxgxgxxxfgxgfxgfgfxxdxvdxgxxafxgxvxxgxfgxxdxgvxxadgxxfvfxxxgvdvdfaxafafxxafxfggaaxaxaxgxxaxxxxxgxxfdfxdxxdaxxaagxxxfxadxxaxxadxfgxxdxfaaxgxxxdxfafxxxvxvxfxaxafxxgddgagagdaadxavgxgfagxagxfdaavfaagvgfvadffvgvgfxavvvaafavgxfaggfaxaggaadxgxavafgvgaxvvxaafaxfagfxdxxggvfxgxfxdvgxvvdxxxfaafdxgxxgffxdvfaggfxaggfxvxgfgggxvxvgadafagaaaxvggafagafxxvaaaavagdgxxavvgfvfxagaxgaffxvgxgxgvaggvgdgdgxxxaggvxgxadfxxxdgvxxxdxgdgggaggdfaxvaggxaaaxxvaavvgagxfagxvvgxfagavvgxxagaddxvgaxvxfxaaxagdfxfaffvgagdaxaavgvgaaxxaxdxfxdxffxxgavxxfavaaxfdavgaavxadxxggaaaggddaggddaxfdxaaavgafafvgxaxxvvagxfxgfxdvgaxxafxxxffvvvdvxxggaaxddxdxxvaxaaxfafaxxxxdgxfxxdvxagxfxfdaxaxgxgggaavvagxvxgdagxvfaxgxvgggvgdgfvxgdggaavvgavgxagxvggadgxxxavdggagxafgfgafdxxxxdxfxavaagagavaffdfxgvfxvgggxgggavaxgxfaxxfdxgadgffaxgaxvvgxdgavxvagaafxaxxgdagvaxavgggvadaafvxfxxaggvggdfvgavvgvfvfxfgdvfxfxdxaggxdaafaaadfxfavaddgfvavxxgxxxgaaadafdfxxvxxfxxgdafxxaxxaggvxgxdvavgggfvaafxfxgxgagadvxxavfffafvagfvgadgavgagxgvdxdxvafgdxvgfaxaaaggxvgaxdxfxxggaagadxgxaggdxxfaagxdfxaxavavxvgdaaavgafgvaxxxfdgxvgxfdxgfaxfxagxaxgxaddgxxfdxaaaxvaxgdvxxdxfdxaaxafgvvxgaxvafxagdxagxgdfvffggfvxxgvxxgaafggaxaffavagggdxfgvggvxxdgvxxdxvxfvgggxxavgxxdvfxvaxxddgvxxdgfxvagaxxvdxggxxgaafxvffaxaxxdaxxvxfgvvgvaxfxxggadxfxfxaaxdxgdgfxdxxdaddagagxxadvdvgaaadxafaxgddxxfxvgxdgxaxdvfdgxgxvxaxfxgggxdfxvvxdaxxagxxdaggvxxaxxxfvxxvagxvgxxxaffvaadxagvaaaaagxafvaafdggxaffdxaavfaffdxggafxaxxvgggafxaaggxadxvxgagvagafxxxxdxaaxdxxaaagvxxaxxxafgfxaxxaxvfxgfxxxfdxaaaxxxffaxxvaxdxvddaaxxgxfdaxfdfdxxaaaxxgfdgfaxxxxagdvxxgxaagxgddvaaxxxdaxxxxxdfgfgxaavfgfdxxxxxxdaxfxgxadfxaxxadfdxaaxfdxgxgxxaxxaxaxvgfgxxxdgadxxxfxxadxxaxdfaddadaaxxaxxaxdgvxaxdxaxxaggdgagdxfxxdvxxagxxaxxxxdfxdxaxxaadxaxgxdxfgfaavaxaxvxffxvgxfvaxxxxgavxvxdxxgadxaxxxxaxvdxxxvxdxaxfxgxgfffxvxdaxxxavxdaxagxaxxaxadggdxxxdfvxvxfxxgaxdxaxaxxadxaxxdfaxxxdgxvfxaagxxxxxxavxxxaxvfaxxaafxgxxaxxagaxxgvdffdfdvxgvxxxaxxgxdvxaxavaaaxadxxavafgaxxgxaxxgvdxaxvxfxavdffggxxaxxxxfdxxvfxxfxxgvdxxaxxavxaxxxgfxfaggxfxxgxaxxxgxgfxdfagdgxafxvaxfdxxxdxdxdxxgagxxxdxxfdaxagfxfaxdxxxgdxxxxxxvgvdvgfxxfgdxafxgaxaggfxdgxadddxxgvxdgaxgvdgdxxxxdfxxvxxxxfadgxxgxxfxxxgxaxxvaxxaagxxfxxxxfxfxxxaxaxxgaxxaxfdgdgxxdxgxdxfvxfdxaxgfxxxadaxxxdxxaxfxfxfxvvdxxxxaagxaaggggxfxxxfxaxxxxgxgxxddgdxaxadxgdxxaxdvxdfxaxxvxdaxxfxxgvdxaddvxxxffffxvxfxxdvdxxxxxgxdfdaxdgvdxfxdxdgxfagdxdfxxaxagxdgxgaxxfadgagxdfaxgdxxfxdvaffvxgfxfxdgxfgaxaaxaaaaxgfdfgxxxxxxvfggaafgaxxdxaxadddxxxxaxxfvfxgaafgafxxfxxaxaxxxadfxxdxfaaxxaxfaxxfgafaagdfxxxfaxxxvddvgxxxdxggxgdgxdxxgxxvfafgxxgxxdaxxgdgxaaavafgfxdaxvfxxaaxfxxdaaxafxfgxgfxgavdgxxgaxfxaxavfxggdfgaxavadxxxfgaaxaaxxxxggaxfadxxaaxdvfdgxxgfgxaxxxxfvxagxavxxfaxadxdxxaxxxgxdxfagadxvaggxdfaxvxgxxdxfaxxxgdfxgxaxxxxdgxxfddggfxgxxvfggxvagagxxgxaxxgaaxagadxgvvfdxdfxaagxvvfaafaxxgvaxdffxdaagdfxaagxgfdxvgaxffaggadxxgdfvvgdggdadagvaaafvaggafvxaagxfxfagdadxxagxggaxgavxfaaavfvdgxaffvxxagdgaagfgaxxgvvgaafxfxxaagvgdadgaxfdadggdxagxaggaagaxgxafxgxgadxxfvvggafvxgfxaxgavxvxvgfgfffavxggxfvfxaxagxadxaaggaagxgaaavxgxgxxdgdafgvxavxvagvxdavxaaaxaxxvgxdgvdxxgxaaxxfaxgagxgxgxaggvfafxgdafxaxgvfvddgxxxvggaggdfdxgxaaxgfdxgfxfvfxafvgxxdxagxdxfgddaffgvvxxddxxgaxavgfaggvagxgxvadgxxxxvfdxaagfaggxxgaddfxaaxxgxavaxavgxdggaaxaxgxgafgagfdxaafgxxfffvaagvvaxdgxaafggafavdvgfdxaafxxxxgadgxaaxffvgxxxgfdxagadavfvvxavgxgdaxgxavffafdfaxfxgxaagaxafafffaxxgvgaggfadvfvavfxaxfagagavgfffvgaxgaagxgvvgfavxggagxfgavgdxfxaxvxfxdafgdxadxxffxavxxafafxdxvfgafagaaggdaagxdxavfffdxxdgdvvgvxxxggdagxxgxvdaxvafvaxgxdgdafxggffffdaxvgxgagxaagaadfgvvdggdgvadfxvdfxxxxfdaxafvaagafgdgaxvfdaxagafagdgxaafxgdaffdxaavgaxaaafggvgxadgdfxaaxddddvvxggvxggagdgdgvgvfgxagxxvadxvgadaddvxdvfvxxvvxagxdvgaagvaagfvadxgdvxaaafvxxgxdggxxdvgagvfxxadxagaxvxgxvffgaxavxxaxvfxxafgavxaxxgxvffdgxfgdgxxfxagvxaxgggxagxggdxfgvgxxgfgfxvggvfdaggxxadxgxxvavaafgfdvxxxfxvxxxvvfxgfdxgdaxxgavggvxgxxafvxvxafdaxvgavfafvfvgdxgaaaxagvffxgaxagvvgxvvxfxxxgfddfagxaxgdxxfavgxgggaaggxaagagaxvgadgvxxxgaxgvgxadxfxvggaxxdxfxfxdaxfxavxfagdaxagxxadxxvavggaaxagffdvgaaxfadvvgaxgagfvxdavavx";
    string file_solutions = "../../src/Techniques/adfgvx/adfgvx_solutions.txt";
    /// ----- ------------------- ------

    // clear the file
    utilities.ClearContents(file_solutions);
    for (int i = key_length_range_column_transpose.first; i <=  key_length_range_column_transpose.second; i++) {
        utilities.WriteContents(file_solutions, "--columnTranspose key size ("+to_string(i)+")--\n");
        vector<pair<string, double>> TenBest;
        double highesValue = 1000000;
        string permutation_key = "";
        for (int j = 0; j < i; j++) {
            permutation_key += to_string(j);
        }
        vector<string> all_permutations = utilities.simplePermutations(permutation_key);
        for (const string & key : all_permutations) {
            // do the column transposition with a possible (column transposition key) key
            string possible_ciphertext = DecryptSingleColumnTranspositionIntKey(key, Ciphertext);
            vector<string> substrings{};
            for(int index = 0; index < possible_ciphertext.length(); index+=2) {
                substrings.push_back(possible_ciphertext.substr(index, 2));
            }
            double n = substrings.size();
            double sum = 0;
            set<string> singles;
            for(string& s: substrings) {
                singles.insert(s);
            }
            for(const string& s: singles) {
                int occurences = count(substrings.begin(), substrings.end(), s);
                sum += occurences * (occurences-1);
            }
            // calculate the index of coincidence
            double ic = (1/(n*(n-1)))*sum;
            // each time we look at the 10 best value for the given key length.
            if(abs(ic - 0.0667) < highesValue) {
                if (TenBest.size() < 10){
                    TenBest.push_back({key, abs(ic - 0.0667)});
                    highesValue = max_element(TenBest.begin(), TenBest.end())->second;
                }
                else{
                    sort(TenBest.begin(),TenBest.end(),compare);
                    TenBest[TenBest.size()-1] = {key, abs(ic - 0.0667)};
                    //TODO oveschrijf de hoogste waarde
                }
            }
        }
        for(auto best : TenBest){
            string best_text  = DecryptSingleColumnTranspositionIntKey(best.first , Ciphertext);
            utilities.WriteContents(file_solutions, "key: " + best.first + " | Ic: " + to_string(best.second) + " | plaintext:  " + best_text+"\n");


            // For each of these permutations, we also calculate the frequency of the pairs:
            map<string, double> occurences{};
            vector<string> substrings{};
            for(int index = 0; index < best_text.length(); index+=2) {
                substrings.push_back(best_text.substr(index, 2));
            }
            set<string> singles;
            for(string& s: substrings) {
                singles.insert(s);
            }
            for(const string& s: singles) {
                occurences.insert({s, (double) count(substrings.begin(), substrings.end(), s)/(double)substrings.size()});
            }

            multimap<double, string> multiMap;

            for(auto& m: occurences){
                multiMap.insert(make_pair(m.second, m.first));
            }
            // put the frequencies underneath the ciphertext in the file
            utilities.WriteContents(file_solutions, "Frequenties: ");
            for(auto m : multiMap){
                utilities.WriteContents(file_solutions, m.second + " -> " + to_string(m.first) +" | ");
            }
            utilities.WriteContents(file_solutions,  "\n\n");
        }
    }

    // Thankfully, there is a solution with an Ic: 0.000454.
    // we are going to decipher these manually like we did in class
    // file: https://docs.google.com/spreadsheets/d/18L9Xed-bFH-7W2jY9kgeEXixlJdJMib6p8IxcVjUxeQ/edit?usp=sharing

    // solution
    cout << ADFGVX.decode(Ciphertext, "012hbid3pl4gqxynfjuk5crms6789vaotzwe", "032145") << endl;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    const auto d = end - begin;
    const auto hrs = std::chrono::duration_cast<std::chrono::hours>(d);
    const auto mins = std::chrono::duration_cast<std::chrono::minutes>(d - hrs);
    const auto secs = std::chrono::duration_cast<std::chrono::seconds>(d - hrs - mins);
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(d - hrs - mins - secs);
    cout << "Ended\nTime: " << hrs.count()  << "h "<< mins.count()  << "m " <<  secs.count()  << "s " << ms.count()  << "ms" << endl;
}
