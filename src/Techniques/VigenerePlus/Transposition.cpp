#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>
#include <limits>
#include "../../Utilities/Utilities.h"

using namespace std;

// I put the specific helper functions in an unnamed namespace, so it is not accessible to the user
namespace {

    vector<vector<double>> BIGRAMSQUARE{{3.40008157684157,2.69262260305957,2.38293189544025,2.46337633776572,3.72422806569787,2.87982813518528,2.69095880781716,3.28851581870791,2.49054923237858,3.69624851126805,2.9251626741056,2.05370349068739,2.43243099636807,1.79219757243754,3.76108865282038,2.70373380444589,4.13749423559963,2.00901166690972,2.05870695840607,1.95218017166687,2.94710793783851,2.71740241745513,3.04272770098262,3.81581140989685,2.57431729135585,3.75033434908219}, //A,A-Z
                                        {2.68809924465431,3.79757972976293,4.13023313468313,4.4843693365975,2.34656628562577,4.7588037478416,5.0282719692697,4.44700096971362,2.99676460155375,4.18471408013958,5.2046473770358,2.79447373428197,4.35303407902197,4.61008082847895,2.72354918231502,4.57459310431446,5.89451053925169,2.97115504465397,3.48678045819694,4.00417479391998,2.7267025491786,4.55642423580126,4.48918459389718,6.15574780645768,2.91722465391391,5.72570116176496}, // B,A-Z
                                        {2.33637480293287,4.16160503422881,3.15495900146205,4.08148812124111,2.33915396934263,4.20836373764191,4.37680660309874,2.33199543104726,2.70924313537199,5.01757843210656,2.77825906142505,2.8813052862996,4.17962058123979,4.36163443192204,2.20878421511598,4.05278707900799,4.43849115056166,2.89440444035591,3.4955136924453,2.56076226398864,2.97275897195214,4.66173699475536,4.22553808366734,5.91162266213017,3.57697320390025,4.87311496994152}, // C,A-Z
                                        {2.3907794982485,2.85009059528792,3.05812177656009,3.0337001310947,2.20405513711652,3.03017577239264,3.24812815254184,2.9744867364217,2.29995950277439,3.7331528595687,3.91512420668598,3.15146415313208,3.08629393072488,3.18250037446987,2.51795403807035,3.13827194410068,4.18363049595913,2.87988053485536,2.61761892853379,2.43835132973027,2.86790376615884,3.54297972839846,2.94509893600899,5.19794196564964,3.28992915780662,4.64450408877784}, // D,A-Z
                                        {1.99911174706151,2.64739317384422,2.22468641212529,1.9670658757195,2.36877511834204,2.51360966534181,2.71752933620732,2.75742608545672,2.43104859811146,3.5365656725572,3.25358623325524,2.27243231875864,2.37713452246012,1.94577978073059,2.50478739668409,2.48901495388631,3.47111873048118,1.74865052742196,1.87948721193091,2.11906511068871,3.07074401305354,2.61165877387098,2.4663297163577,2.88389905049225,2.75919919159084,3.96801056832909}, // E,A-Z
                                        {2.71379985420777,3.68740976666134,3.43978012745797,3.76198125774432,2.70498570176465,2.8516009090294,3.83124261664974,3.45761125067452,2.55694053422631,4.20475196911783,4.27624325260515,3.17487462662503,3.5385329222899,3.90806296507988,2.35889082484959,3.55677338567711,4.95916835147899,2.71476497628451,3.32469243887351,2.49930231105726,3.13912105169195,4.24729118525167,3.63334242834289,5.35004879123752,3.73829288082392,5.14193885717678}, // F,A-Z
                                        {2.58514041189457,3.56240856671014,3.52210854586017,3.69151852313723,2.47678201744114,3.46997494599249,3.46908787388654,2.64112404868185,2.78444815720697,4.38805532782321,4.42150510047575,3.22482001094793,3.56456489122869,3.25093094383129,2.72268314678783,3.55124934133782,4.85956062211078,2.79142365483197,3.0425376882975,2.76972997513526,3.05973807923104,4.36457513621844,3.44055496615139,5.46628286950821,3.64475932362189,5.18084038646378}, // G,A-Z
                                        {2.07993586662078,3.6298588635438,3.47721737236327,3.71747237014816,1.6329153697023,3.71458461701965,4.00282718260416,3.51204754383877,2.19663940572037,4.35735984542613,4.31288375941207,3.56791018896634,3.50460041414714,3.49477562126702,2.34079288658352,3.64527157506193,4.63054210551403,3.05122803425739,3.24460589678436,2.71413139418868,3.1931319408294,4.34024568081807,3.48877183720043,5.75933431774711,3.47559480566542,5.06692281032666}, // H,A-Z
                                        {2.63581116047045,3.2211851701076,2.30409861049654,2.52541700453045,2.53879587368039,2.87695531678389,2.65677947395458,3.8500827013191,3.85262113058005,4.29520065682408,3.22341715210596,2.38358931574512,2.61287575316426,1.69302770075723,2.3093545870779,3.11103253525796,4.17105888796049,2.56840538361185,2.06360814650584,2.056817986623,3.87496138266966,2.67546428784301,3.67113982048792,3.69173182502354,4.64307559633005,3.36503297745977}, // I,A-Z
                                        {3.40220125919924,5.34854475901621,5.24197252514512,5.29539492857051,3.46348593792481,5.53415145778459,5.55588568462303,5.31450725341927,4.08252895531604,5.42947746649297,5.49079539858458,5.55135799966947,5.28685424512892,5.47597057883497,3.20111492854056,5.09782774468779,6.77736133416132,4.73025913346373,5.04121875685114,5.32609808612922,3.16980013037945,5.68529030694673,5.42953146978599,6.76257792991556,5.87827478582257,6.17968437637297}, // J,A-Z
                                        {3.18364613190885,3.97516582779286,4.01263166310263,4.19188185650987,2.60852160300311,3.90564774428833,4.31519985863287,3.82292170591723,2.87139683791022,4.75044684310587,4.56104188049533,3.7083695723642,3.94960465004563,3.35626899701162,3.39087941395432,4.06111167022497,5.49272753853078,3.9308734408033,3.12705475300162,3.47633584989004,3.93121791563727,4.7714823888043,3.77878746128577,5.92977842202825,3.89294100119547,5.58699083024719}, // K,A-Z
                                        {2.27081663350065,3.24431194216414,3.26890380309754,2.62536202537249,2.15326413308802,3.20412929369776,3.66906623320205,3.53071274129643,2.2687072451066,4.29672146833102,3.5698761593893,2.24431291169335,3.2902280529855,3.75949823338669,2.4428766728765,3.23038876548593,4.74857385992184,3.45833548437839,2.69760642048799,2.80228784591505,2.99215576447413,3.54307721816893,3.37183406017194,5.44649244620173,2.49784760782051,4.87763781237971}, // L,A-Z
                                        {2.29687706591741,3.02081540999177,3.59382453892281,3.9536397049647,2.20072757337131,3.78153964892094,4.18085104823936,3.78411201074682,2.55064563919286,4.50794218480869,4.59041516748431,3.95599117710039,3.06413055606849,3.88895545536611,2.52360300823475,2.74184999706151,5.30633794955565,3.8159474714938,3.04229627607751,3.15075285594682,3.06119214261962,4.50135806980304,3.66387120600704,5.48208366738643,3.34605794857322,5.37413621412134}, // M,A-Z
                                        {2.26395328352164,3.07927139656317,2.45363733619669,1.97131008485837,2.19923228383023,2.94126411760583,2.04967856372443,3.04312128604849,2.39405073937517,3.50790822225938,3.15256803647364,3.06852098807415,3.0564661699083,2.92149340579594,2.3595720692899,3.16341619848542,4.29859504536064,3.25685058435923,2.30738802760524,1.93088128698962,3.06388684730124,3.29455621795666,3.0110013289036,4.7617415416322,2.99807970370536,4.21026487830924}, // N,A-Z
                                        {2.81937745057988,2.8426312911117,2.75241016760461,2.7545016623832,3.21820966255784,2.15101664385662,3.01647897641069,3.12339303872727,2.90863257777146,3.81564319941812,3.10473011848226,2.49833900207673,2.31231323581397,1.8806698686428,2.62862643434737,2.61638947594339,4.54713538472843,1.97574300347484,2.50247891105705,2.33296079428663,2.14296663723472,2.76961036541997,2.47123556359971,3.82293306287694,3.34969094315217,4.27690590495624}, // 0,A-Z
                                        {2.55423771599674,4.0684768903693,4.03350426233248,4.19947824791528,2.44351737994808,4.01454773604498,4.31134241307122,3.18482719879445,2.89088545184268,4.96340352219388,4.71673149658133,2.64413098919798,3.66684390504337,4.5164941628855,2.55971209567272,2.94806709657595,5.36622217410109,2.51561481934774,3.25986277260145,3.05469152721812,3.04951964840482,4.95370831274684,3.91128600956621,5.8024964024991,4.03804216034473,5.6492611361208}, // P,A-Z
                                        {4.7694516851938,5.19962454140491,5.60785623664021,5.69747888593776,5.85630204047313,5.692502955222,6.22647266305951,5.54694779751292,4.7702793972685,6.50814601589798,6.32990264896015,5.65349160286716,5.54546411555584,6.05520159201852,5.66304797588373,5.85328259969935,6.23813227560451,5.85956062211078,5.31685496533184,5.40765220547571,3.01582246977877,6.01141016921751,5.09595721677618,6.75223709657734,5.97721950314851,7.18874050038874}, // Q,A-Z
                                        {2.1788409571826,3.11134507941016,2.79241266548641,2.68042066898458,1.8511129736733,3.09981605383648,2.96882512188395,3.16333134151109,2.19444467323949,3.92143716213475,2.98351679707418,2.95436370197172,2.76796052833853,2.78680880313743,2.17005827599218,3.08102334227985,4.44018425474087,2.8653254414161,2.30880006819118,2.30434857699622,2.90912594008007,3.20575169123372,3.11111243382228,5.04870408941346,2.69198184743931,4.58116294222739}, // R,A-Z
                                        {2.1576188084399,2.8913173666085,2.60244920187753,3.05131291246292,2.13714326756364,2.85242410165172,3.32546651177081,2.41128449642076,2.2249722133626,3.78805329030672,3.27005726471561,2.93997822924649,2.88920557470141,3.01701509121604,2.25743465574143,2.61179782443343,3.73262075298263,3.09012050445746,2.35907620601241,1.90335682333027,2.63455408484325,3.69038907954013,2.6977174681104,4.92854129728078,3.29066795567573,4.73367800345164}, // S,A-Z
                                        {2.21846681538926,3.05435174063892,2.92016110782507,3.26547501188348,2.00960115445041,3.10846816863768,3.45119432773408,1.56772067295514,2.00355599348556,3.88811939928295,3.85033167933877,2.90325255223735,3.06072674213543,3.38496183129058,1.9720545482444,3.14869975532593,4.43419832647682,2.43665839742363,2.35891951289511,2.34882559496127,2.70763098942628,3.79194978937491,2.68600844730956,5.18632757519975,2.73232468460678,4.18872964316241}, // T,A-Z
                                        {2.97408613004639,3.16010128557916,2.87680622518484,3.09188819033792,2.94324219766617,3.78962823927694,2.9517423964821,4.10526219640642,3.09413437760809,4.69058754234863,3.92419841375974,2.62842950835358,2.99346171224808,2.4529791413055,3.82304798529341,2.91105369950457,5.26694258638545,2.39680643705044,2.4400167770491,2.45585387206508,4.83626166017387,4.30945820686422,4.08845367089247,4.47508798210162,3.910019554384,4.44912295459786}, // U,A-Z
                                        {3.02191144098729,5.17063468137437,4.86486989384823,4.70336896176901,2.16872015370459,5.18734679252938,5.22791311042282,5.15584844908052,2.66369398025337,5.57777631594804,5.57637297899227,4.9454189233869,5.0915327875071,5.11630677442035,3.28308105693053,4.83948379290602,6.4632956005211,4.65174942173769,4.3260704222305,4.83716503991494,4.71771087037203,5.28702925801942,4.97685750373488,6.13183564905227,4.26838979575871,6.21544767262489}, // V,A-Z
                                        {2.40958754776808,4.03949938755697,3.98423873910224,3.99976583890228,2.51581457674915,4.10928402988773,4.4901118615568,2.56207358158696,2.45368315260711,4.63835925365775,4.46281720620725,3.81781654675524,3.93201674262449,3.0736514788346,2.67654002934018,4.12838537534249,5.42517881604996,3.54714069497979,3.33732336174425,3.52152343812366,4.37849837846442,4.83019382729709,3.80684575711817,5.96583831425782,3.89266558074789,4.91296860022381}, // W,A-Z
                                        {3.67965900576622,4.66258129311373,3.79204622011093,4.85701683359063,3.82035597995143,4.58270096185316,5.04162755662261,4.41422614147763,3.62528653805716,5.60940612467812,5.500734065074,4.86076158805001,4.53041559766576,5.09514373178051,4.31126014201977,3.37091646317492,5.90221987605387,4.68143410626348,4.44740033909268,3.45693050050874,4.4670093580952,5.14290081186605,4.55917800761012,5.09118572870978,4.66125330130775,6.31741780655644}, // X,A-Z
                                        {2.77618707979261,3.20505204679329,3.1406244288353,3.30908418627499,2.82303161367312,3.27318163139997,3.61508909620118,3.27582169425258,2.98644547531517,4.05762731015119,4.04266453885442,3.33185221961693,3.23514077414625,3.4639805628124,2.67740646353394,3.22396533792238,4.69164787427943,3.33013048253483,2.75854901633142,2.80890742750747,3.79359390424858,4.02154241251668,3.10710211427284,5.40685695855756,4.11348951271837,4.74224216681822}, // Y,A-Z
                                        {3.66782719046757,4.93130193352892,5.02272292746024,5.11862343836115,3.40293518514083,5.17865265339021,5.21480487151343,4.60392887735217,3.82698906205153,5.78056112726142,5.2509719333388,4.73259687776872,4.97281981835226,5.25134800016724,4.00851628697642,5.15318212258973,5.87449697423233,5.12155004242902,4.65820692826717,4.88036667553548,4.58075729197908,5.47937966698393,4.79789997990926,6.24443411989185,4.61112151652201,4.29096618231055} // Z,A-Z
    };

    vector<vector<char>> makeEmptyMatrix(const string &key, const string &Ciphertext){
        vector<vector<char>> result;
        int ciphertextSize = Ciphertext.size();
        int rowCount = ceil( Ciphertext.size() / key.size());
        for (int i = 0; i <= rowCount; i++) {
            vector<char> row;
            int elementsPerRow;
            if (ciphertextSize >= key.size()){
                elementsPerRow = key.size();
            }
            else{
                elementsPerRow = ciphertextSize % key.size() ;
            }
            for (int j = 0; j < elementsPerRow; j++) {
                row.push_back('_');
            }
            result.push_back(row);
            ciphertextSize -= key.size();
        }
        return result;
    }

    template<typename T>
    std::vector<T> flatten(std::vector<std::vector<T>> const &vec){
        std::vector<T> flattened;
        for (auto const &v: vec) {
            flattened.insert(flattened.end(), v.begin(), v.end());
        }
    return flattened;
    }

}

string DecryptSingleColumnTranspositionIntKey(const string &key, const string &Ciphertext) {

    // make the empty matrix
    vector<vector<char>> CiphertextMatrix = makeEmptyMatrix(key, Ciphertext);

    // fill the matrix
    string text = Ciphertext;
    for (const char &i : key) {
        int index = i - '0';
        for (int j = 0; j < CiphertextMatrix.size(); j++) {
            if (CiphertextMatrix[j].size() > index && text.size() > 0){
                CiphertextMatrix[j][index] = (char) tolower(text[0]);
                text.erase(text.begin());
            }
        }
    }

    // make list of matrix
    vector<char> CiphertextVector = flatten(CiphertextMatrix);

    // make string of matrix
    string result(CiphertextVector.begin(), CiphertextVector.end());
    return result;
}


/// ----- code for deciphering ------

struct SequenceValue {
    vector<int> indexes;
    vector<int> spacing;
};

map<string, SequenceValue> FindRepeatedSequences(const string &Ciphertext){
    // do a kasiski test
    map<string, SequenceValue> RepeatedSequences;
    for (int i = 0; i < Ciphertext.size()-2; i++) {
        string triplet = Ciphertext.substr(i,3);
        // if triplet not registered yet add it to the RepeatedSequences
        if (RepeatedSequences.count(triplet) == 0){
            SequenceValue value;
            value.indexes.push_back(i);
            RepeatedSequences.insert({triplet, value});
        }
        else{
            // If we encounter the index again we will add the index
            SequenceValue *p = &RepeatedSequences[triplet];
            int last_index = p->indexes.back();
            p->indexes.push_back(i);
            int current_index = i;
            // we are going to calculate the distance from the current index and the previous index
            p->spacing.push_back(current_index-last_index);
        }
        if (i < Ciphertext.size() -3){
            string Quadruplets = Ciphertext.substr(i,4);
            if (RepeatedSequences.count(Quadruplets) == 0){
                SequenceValue value;
                value.indexes.push_back(i);
                RepeatedSequences.insert({Quadruplets, value});
            }
            else{
                // If we encounter the index again we will add the index
                SequenceValue *p = &RepeatedSequences[Quadruplets];
                int last_index = p->indexes.back();
                p->indexes.push_back(i);
                int current_index = i;
                // we are going to calculate the distance from the current index and the previous index
                p->spacing.push_back(current_index-last_index);
            }
        }
    }
    return RepeatedSequences;
}

vector<int> findDivisors(int n, int min_key_length, int max_key_length) {
    assert(n > 0);
    vector<int> devisors;
    // we assume that the key is not greater than 20
    for (int i = min_key_length; i <= max_key_length; i++) {
        if (n % i == 0) {
            devisors.push_back(i);
        }
    }
    return devisors;
}

pair<bool, vector<int>> IsPossibleVinegere(const map<string, SequenceValue>& repeated_sequences, const int& min_key_length ,const int& max_key_length ){
    assert(max_key_length > 1);
    map<int, int> devisors;
    for (auto const& sequence : repeated_sequences){
        for (const int & space : sequence.second.spacing){
            vector<int> devisorsList = findDivisors(space, min_key_length, max_key_length);
            for(const int &i : devisorsList){
                if (devisors.count(i) == 0){
                    devisors.insert({i, 1});
                }
                else{
                    devisors[i] += 1;
                }
            }
        }
    }

    bool isPossibleVinegere = false;

    // find outliers
    vector<int> devisors_values;
    devisors_values.reserve(devisors.size());
    int sum = 0;
    for (auto const& devisor : devisors){
        devisors_values.push_back(devisor.second);
        sum += devisor.second;
    }
    int mean = sum / devisors_values.size();
    vector<int> key_lengths;
    for (auto const& devisor : devisors) {
        // we assume that the key length is greater than 4
        //cout << devisor.second << " > " <<  (2*mean) << endl;
        if (devisor.second > (2*mean) && devisor.first > 4) {
            key_lengths.push_back(devisor.first);
            isPossibleVinegere = true;
        }
    }


    return make_pair(isPossibleVinegere, key_lengths);
}

struct Keys {
    string vinegere;
    vector<int> vinegereLenght;
    string columnTranspose;

    bool operator<(const Keys& rhs) const{
        return columnTranspose < rhs.columnTranspose;
    }

    bool operator>(const Keys& rhs) const{
        return columnTranspose > rhs.columnTranspose;
    }

    bool operator==(const Keys& rhs) const{
        return columnTranspose == rhs.columnTranspose && vinegere == rhs.vinegere && vinegereLenght == rhs.vinegereLenght;
    }
};

map<Keys, string> GetPossibleCipherByKeyLength(const int &keyLengthColumnTranspose, const string &Ciphertext, const string &inputfile, const pair<int,int> & keyLengthVinegere){
    assert(keyLengthColumnTranspose > 1);
    assert(keyLengthVinegere.first > 1);
    assert(keyLengthVinegere.second > 1);
    assert(keyLengthVinegere.first < keyLengthVinegere.second);
    assert(inputfile != "");
    map<Keys, string> results;
    Utilities utilities;
    string permutation_key = "";
    for (int i = 0; i < keyLengthColumnTranspose; i++) {
        permutation_key += to_string(i);
    }
    vector<string> all_permutations = utilities.simplePermutations(permutation_key);
    for (const string & key : all_permutations) {
        // do the column transposition with a possible (column transposition key) key
        string possible_ciphertext = DecryptSingleColumnTranspositionIntKey(key, Ciphertext);
        // find the repeated sequence in the possible ciphertexts
        map<string, SequenceValue> repeated_sequences = FindRepeatedSequences(possible_ciphertext);
        // test whether the outcome can be a possible vinegere cipher
        auto possible_vinegere = IsPossibleVinegere(repeated_sequences, keyLengthVinegere.first, keyLengthVinegere.second);
        // if that is the case we write it to a file
        if( possible_vinegere.first ){
            string possible_key_sizes = " ";
            Keys key_;
            for (const int &i: possible_vinegere.second ){
                possible_key_sizes += to_string(i) +" ";
                key_.vinegereLenght.push_back(i);
            }
            utilities.WriteContents(inputfile, key+"(possible vinegere keys:"+ possible_key_sizes +"): "+possible_ciphertext+"\n");

            key_.columnTranspose = key;
            results[key_] = possible_ciphertext;
        }
    }
    return results;
}


map<Keys, string> ReadPossibleColumnTranspositions(const string & inputfile){
    map<Keys, string> possible_column_transpositions;

    // initialize delimiters
    string delimiter1 = "--";
    string delimiter2 = "(";
    string delimiter3 = ")";
    string delimiter4 = ":";
    string delimiter5 = " ";

    ifstream file(inputfile);
    // read from file and populate possible_column_transpositions
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            auto pos = line.find(delimiter1);
            if (pos == string::npos){
                Keys key;

                string column_transposition_key = line.substr(0, line.find(delimiter2));
                key.columnTranspose = column_transposition_key;

                string possible_vinegere_keylengths_string = line.substr(line.find(delimiter4)+1, (line.find(delimiter3)  - line.find(delimiter4)) - 1);
                for (const char& key_size : possible_vinegere_keylengths_string){
                    if (key_size != ' '){
                        int key_size_int = key_size - '0';
                        key.vinegereLenght.push_back(key_size_int);
                    }
                }

                string cipthertext = line.substr(line.find_last_of(delimiter4)+2);
                possible_column_transpositions.insert({key, cipthertext});
            }
        }
        file.close();
    }
    return possible_column_transpositions;
}

pair<int,int> getFilter(const string & bigram){
    assert(bigram[0] >= 97 && bigram[1] <= 122);

    int first = (bigram[0] - 97) % 26;
    int second = (bigram[1] - 97) % 26;

    return {(26 - first) % 26, (26 - second) % 26};
}

string BruteForceKey(const int &keylenght, const string &Ciphertext){
    struct {
        char first;
        char second;
        double entropy;
    } best, previous, zero;

    string key;

    previous.entropy = std::numeric_limits<double>::max();

    for (int keyIndex=0; keyIndex < keylenght; keyIndex++){
        // Generates a large entrpoy initially so any pair will be better
        best.entropy = std::numeric_limits<double>::max();
        string alphabet = "abcdefghijklmnopqrstuvwxyz";
        // Loop through the first half of the bigrams
        for( const char &first: alphabet) {
            // Loop through the second half of the bigrams
            for( const char &second: alphabet) {
                string bigram;
                bigram += first;
                bigram += second;
                double entropy = 0.0;
                pair<int,int> filter = getFilter(bigram);
                for (int index=keyIndex; index < Ciphertext.size() -1; index += keylenght){
                    int first_plain = (Ciphertext[index] - 97 + filter.first) % 26;
                    int second_plain = (Ciphertext[index + 1] - 97 + filter.second) % 26;
                    // add the entropy for the plaintext bigram to the key bigram's entropy
                    entropy += BIGRAMSQUARE[first_plain][second_plain];
                }
                if(entropy < best.entropy){
                    best.first = first;
                    best.second = second;
                    best.entropy = entropy;
                }
            }
        }

        if (keyIndex == 0){
            zero.first = best.first;
            zero.second = best.second;
            zero.entropy = best.entropy;

            key.push_back(best.first);
        }
        else if (keyIndex == (keylenght - 1)){
            key.push_back(best.first);
        }
        else{
            if (previous.entropy <= best.entropy) {
                key.push_back(previous.second);
            }
            else {
                key.push_back(best.first);
            }
        }
        previous.first = best.first;
        previous.second = best.second;
        previous.entropy = best.entropy;
    }
    // Check if last best bigram is better then key index zero
    if (best.entropy < zero.entropy) {
        key[0] = best.second;
    }
    return key;
}

double getEntropy(const string &Plaintext){
    double entropy = 0.0;
    for (int i=0; i <= Plaintext.size()-1; i++){
        pair<char, char> bigram{Plaintext[i], Plaintext[i+1]};
        entropy += BIGRAMSQUARE[bigram.first - 97][bigram.second - 97];
    }
    return entropy;
}

void DecipherVinegere(const int &keylenght, const string &Ciphertext, const string &inputfile, const string &ColumnTransposeKey){
    Utilities utilities;

    string key = BruteForceKey(keylenght, Ciphertext);
    Vigenere vinegere(key);
    string Plaintext = vinegere.decrypt(Ciphertext);
    double entropy = getEntropy(Plaintext);
    if (entropy <= 7000){
        string result = "ColumnTransposeKey: " + ColumnTransposeKey + " | VigenereKey: " + key + " | entropy: " + to_string(entropy)+ " | plaintext: " + Plaintext + "\n";
        utilities.WriteContents(inputfile, result);
    }
}