#include <string>
#include <cstring>

#include <benchmark/benchmark.h>

#include <utfcaseconv/utf8.h>

static constexpr char ascii[] =
    "Call me Ishmael. Some years ago - never mind how long precisely - having "
    "little or no money in my purse, and nothing particular to interest me on "
    "shore, I thought I would sail about a little and see the watery part of "
    "the world. It is a way I have of driving off the spleen and regulating "
    "the circulation. Whenever I find myself growing grim about the mouth; "
    "whenever it is a damp, drizzly November in my soul; whenever I find "
    "myself involuntarily pausing before coffin warehouses, and bringing up "
    "the rear of every funeral I meet; and especially whenever my hypos get "
    "such an upper hand of me, that it requires a strong moral principle to "
    "prevent me from deliberately stepping into the street, and methodically "
    "knocking people’s hats off - then, I account it high time to get to sea "
    "as soon as I can. This is my substitute for pistol and ball. With a "
    "philosophical flourish Cato throws himself upon his sword; I quietly take "
    "to the ship. There is nothing surprising in this. If they but knew it, "
    "almost all men in their degree, some time or other, cherish very nearly "
    "the same feelings towards the ocean with me."
    "There now is your insular city of the Manhattoes, belted round by wharves "
    "as Indian isles by coral reefs - commerce surrounds it with her surf. "
    "Right and left, the streets take you waterward. Its extreme downtown is "
    "the battery, where that noble mole is washed by waves, and cooled by "
    "breezes, which a few hours previous were out of sight of land. Look at "
    "the crowds of water-gazers there."
    "Circumambulate the city of a dreamy Sabbath afternoon. Go from Corlears "
    "Hook to Coenties Slip, and from thence, by Whitehall, northward. What do "
    "you see? - Posted like silent sentinels all around the town, stand "
    "thousands upon thousands of mortal men fixed in ocean reveries. Some "
    "leaning against the spiles; some seated upon the pier-heads; some looking "
    "over the bulwarks of ships from China; some high aloft in the rigging, as "
    "if striving to get a still better seaward peep. But these are all "
    "landsmen; of week days pent up in lath and plaster - tied to counters, "
    "nailed to benches, clinched to desks. How then is this? Are the green "
    "fields gone? What do they here?"
    "But look! here come more crowds, pacing straight for the water, and "
    "seemingly bound for a dive. Strange! Nothing will content them but the "
    "extremest limit of the land; loitering under the shady lee of yonder "
    "warehouses will not suffice. No. They must get just as nigh the water as "
    "they possibly can without falling in. And there they stand - miles of "
    "them - leagues. Inlanders all, they come from lanes and alleys, streets "
    "and avenues - north, east, south, and west. Yet here they all unite. Tell "
    "me, does the magnetic virtue of the needles of the compasses of all those "
    "ships attract them thither?"
    "Once more. Say you are in the country; in some high land of lakes. Take "
    "almost any path you please, and ten to one it carries you down in a dale, "
    "and leaves you there by a pool in the stream. There is magic in it. Let "
    "the most absent-minded of men be plunged in his deepest reveries - stand "
    "that man on his legs, set his feet a-going, and he will infallibly lead "
    "you to water, if water there be in all that region. Should you ever be "
    "athirst in the great American desert, try this experiment, if your "
    "caravan happen to be supplied with a metaphysical professor. Yes, as "
    "every one knows, meditation and water are wedded for ever."
    "(c) Herman Melville, Moby-Dick, or The Whale, 1851";

// just a translited version of the quote above
static constexpr char cyrillic[] =
    "Цалл ме Ишмаел. Соме ыеарс аго - невер минд хов лонг прециселы - хавинг "
    "литтле ор но монеы ин мы пурсе, анд нотхинг партицулар то интерест ме он "
    "шоре, И тхоугхт И воулд саил абоут а литтле анд сее тхе ватеры парт оф "
    "тхе ворлд. Ит ис а ваы И хаве оф дривинг офф тхе сплеен анд регулатинг "
    "тхе цирцулатион. Вхеневер И финд мыселф гровинг грим абоут тхе моутх; "
    "вхеневер ит ис а дамп, дриззлы Новембер ин мы соул; вхеневер И финд "
    "мыселф инволунтарилы паусинг бефоре цоффин варэоусес, анд брингинг уп тхе "
    "реар оф еверы фунерал И меет; анд еспециаллы вхеневер мы хыпос гет суч ан "
    "уппер ханд оф ме, тхат ит реqуирес а стронг морал принципле то превент ме "
    "фром делиберателы степпинг инто тхе стреет, анд метходицаллы кноцкинг "
    "пеопле’с хатс офф - тхен, И аццоунт ит хигх тиме то гет то сеа ас соон ас "
    "И цан. Тхис ис мы субституте фор пистол анд балл. Витх а пхилосопхицал "
    "флоуриш Цато тхровс химселф упон хис сворд; И qуиетлы таке то тхе шип. "
    "Тхере ис нотхинг сурприсинг ин тхис. Иф тхеы бут кнев ит, алмост алл мен "
    "ин тхеир дегрее, соме тиме ор отхер, чериш веры неарлы тхе саме феелингс "
    "товардс тхе оцеан витх ме."
    "Тхере нов ис ёур инсулар циты оф тхе Манхаттоес, белтед роунд бы вхарвес "
    "ас Индиан ислес бы цорал реефс - цоммерце сурроундс ит витх хер сурф. "
    "Ригхт анд лефт, тхе стреетс таке ёу ватервард. Итс еxтреме довнтовн ис "
    "тхе баттеры, вхере тхат нобле моле ис вашед бы вавес, анд цоолед бы "
    "бреезес, вхич а фев хоурс превиоус вере оут оф сигхт оф ланд. Лоок ат тхе "
    "цровдс оф ватер-газерс тхере."
    "Цирцумамбулате тхе циты оф а дреамы Саббатх афтерноон. Го фром Цорлеарс "
    "Хоок то Цоентиес Слип, анд фром тхенце, бы Вхитэалл, нортхвард. Вхат до "
    "ёу сее? - Постед лике силент сентинелс алл ароунд тхе товн, станд "
    "тхоусандс упон тхоусандс оф мортал мен фиxед ин оцеан ревериес. Соме "
    "леанинг агаинст тхе спилес; соме сеатед упон тхе пиер-хеадс; соме лоокинг "
    "овер тхе булваркс оф шипс фром Чина; соме хигх алофт ин тхе риггинг, ас "
    "иф стривинг то гет а стилл беттер сеавард пееп. Бут тхесе аре алл "
    "ландсмен; оф веек даыс пент уп ин латх анд пластер - тиед то цоунтерс, "
    "наилед то бенчес, цлинчед то дескс. Хов тхен ис тхис? Аре тхе греен "
    "фиелдс гоне? Вхат до тхеы хере?"
    "Бут лоок! хере цоме море цровдс, пацинг страигхт фор тхе ватер, анд "
    "сееминглы боунд фор а диве. Странге! Нотхинг вилл цонтент тхем бут тхе "
    "еxтремест лимит оф тхе ланд; лоитеринг ундер тхе шады лее оф ёндер "
    "варэоусес вилл нот суффице. Но. Тхеы муст гет юст ас нигх тхе ватер ас "
    "тхеы поссиблы цан витхоут фаллинг ин. Анд тхере тхеы станд - милес оф "
    "тхем - леагуес. Инландерс алл, тхеы цоме фром ланес анд аллеыс, стреетс "
    "анд авенуес - нортх, еаст, соутх, анд вест. Ыет хере тхеы алл уните. Телл "
    "ме, доес тхе магнетиц виртуе оф тхе неедлес оф тхе цомпассес оф алл тхосе "
    "шипс аттрацт тхем тхитхер?"
    "Онце море. Саы ёу аре ин тхе цоунтры; ин соме хигх ланд оф лакес. Таке "
    "алмост аны патх ёу плеасе, анд тен то оне ит царриес ёу довн ин а дале, "
    "анд леавес ёу тхере бы а поол ин тхе стреам. Тхере ис магиц ин ит. Лет "
    "тхе мост абсент-миндед оф мен бе плунгед ин хис деепест ревериес - станд "
    "тхат ман он хис легс, сет хис феет а-гоинг, анд хе вилл инфаллиблы леад "
    "ёу то ватер, иф ватер тхере бе ин алл тхат регион. Шоулд ёу евер бе "
    "атхирст ин тхе греат Америцан десерт, тры тхис еxперимент, иф ёур цараван "
    "хаппен то бе супплиед витх а метапхысицал профессор. Ыес, ас еверы оне "
    "кновс, медитатион анд ватер аре веддед фор евер."
    "(ц) Херман Мелвилле, Мобы-Дицк, ор Тхе Вхале, 1851";

// a, o, e are replaced to cyrillic
static constexpr char mixed[] =
    "Cаll mе Ishmаеl. Sоmе yеаrs аgо - nеvеr mind hоw lоng prеcisеly - hаving "
    "littlе оr nо mоnеy in my pursе, аnd nоthing pаrticulаr tо intеrеst mе оn "
    "shоrе, I thоught I wоuld sаil аbоut а littlе аnd sее thе wаtеry pаrt оf "
    "thе wоrld. It is а wаy I hаvе оf driving оff thе splееn аnd rеgulаting "
    "thе circulаtiоn. Whеnеvеr I find mysеlf grоwing grim аbоut thе mоuth; "
    "whеnеvеr it is а dаmp, drizzly Nоvеmbеr in my sоul; whеnеvеr I find "
    "mysеlf invоluntаrily pаusing bеfоrе cоffin wаrеhоusеs, аnd bringing up "
    "thе rеаr оf еvеry funеrаl I mееt; аnd еspеciаlly whеnеvеr my hypоs gеt "
    "such аn uppеr hаnd оf mе, thаt it rеquirеs а strоng mоrаl principlе tо "
    "prеvеnt mе frоm dеlibеrаtеly stеpping intо thе strееt, аnd mеthоdicаlly "
    "knоcking pеоplе’s hаts оff - thеn, I аccоunt it high timе tо gеt tо sеа "
    "аs sооn аs I cаn. This is my substitutе fоr pistоl аnd bаll. With а "
    "philоsоphicаl flоurish Cаtо thrоws himsеlf upоn his swоrd; I quiеtly tаkе "
    "tо thе ship. Thеrе is nоthing surprising in this. If thеy but knеw it, "
    "аlmоst аll mеn in thеir dеgrее, sоmе timе оr оthеr, chеrish vеry nеаrly "
    "thе sаmе fееlings tоwаrds thе оcеаn with mе."
    "Thеrе nоw is yоur insulаr city оf thе Mаnhаttоеs, bеltеd rоund by whаrvеs "
    "аs Indiаn islеs by cоrаl rееfs - cоmmеrcе surrоunds it with hеr surf. "
    "Right аnd lеft, thе strееts tаkе yоu wаtеrwаrd. Its еxtrеmе dоwntоwn is "
    "thе bаttеry, whеrе thаt nоblе mоlе is wаshеd by wаvеs, аnd cооlеd by "
    "brееzеs, which а fеw hоurs prеviоus wеrе оut оf sight оf lаnd. Lооk аt "
    "thе crоwds оf wаtеr-gаzеrs thеrе."
    "Circumаmbulаtе thе city оf а drеаmy Sаbbаth аftеrnооn. Gо frоm Cоrlеаrs "
    "Hооk tо Cоеntiеs Slip, аnd frоm thеncе, by Whitеhаll, nоrthwаrd. Whаt dо "
    "yоu sее? - Pоstеd likе silеnt sеntinеls аll аrоund thе tоwn, stаnd "
    "thоusаnds upоn thоusаnds оf mоrtаl mеn fixеd in оcеаn rеvеriеs. Sоmе "
    "lеаning аgаinst thе spilеs; sоmе sеаtеd upоn thе piеr-hеаds; sоmе lооking "
    "оvеr thе bulwаrks оf ships frоm Chinа; sоmе high аlоft in thе rigging, аs "
    "if striving tо gеt а still bеttеr sеаwаrd pееp. But thеsе аrе аll "
    "lаndsmеn; оf wееk dаys pеnt up in lаth аnd plаstеr - tiеd tо cоuntеrs, "
    "nаilеd tо bеnchеs, clinchеd tо dеsks. Hоw thеn is this? аrе thе grееn "
    "fiеlds gоnе? Whаt dо thеy hеrе?"
    "But lооk! hеrе cоmе mоrе crоwds, pаcing strаight fоr thе wаtеr, аnd "
    "sееmingly bоund fоr а divе. Strаngе! Nоthing will cоntеnt thеm but thе "
    "еxtrеmеst limit оf thе lаnd; lоitеring undеr thе shаdy lее оf yоndеr "
    "wаrеhоusеs will nоt sufficе. Nо. Thеy must gеt just аs nigh thе wаtеr аs "
    "thеy pоssibly cаn withоut fаlling in. аnd thеrе thеy stаnd - milеs оf "
    "thеm - lеаguеs. Inlаndеrs аll, thеy cоmе frоm lаnеs аnd аllеys, strееts "
    "аnd аvеnuеs - nоrth, еаst, sоuth, аnd wеst. Yеt hеrе thеy аll unitе. Tеll "
    "mе, dоеs thе mаgnеtic virtuе оf thе nееdlеs оf thе cоmpаssеs оf аll thоsе "
    "ships аttrаct thеm thithеr?"
    "оncе mоrе. Sаy yоu аrе in thе cоuntry; in sоmе high lаnd оf lаkеs. Tаkе "
    "аlmоst аny pаth yоu plеаsе, аnd tеn tо оnе it cаrriеs yоu dоwn in а dаlе, "
    "аnd lеаvеs yоu thеrе by а pооl in thе strеаm. Thеrе is mаgic in it. Lеt "
    "thе mоst аbsеnt-mindеd оf mеn bе plungеd in his dееpеst rеvеriеs - stаnd "
    "thаt mаn оn his lеgs, sеt his fееt а-gоing, аnd hе will infаllibly lеаd "
    "yоu tо wаtеr, if wаtеr thеrе bе in аll thаt rеgiоn. Shоuld yоu еvеr bе "
    "аthirst in thе grеаt аmеricаn dеsеrt, try this еxpеrimеnt, if yоur "
    "cаrаvаn hаppеn tо bе suppliеd with а mеtаphysicаl prоfеssоr. Yеs, аs "
    "еvеry оnе knоws, mеditаtiоn аnd wаtеr аrе wеddеd fоr еvеr."
    "(c) Hеrmаn Mеlvillе, Mоby-Dick, оr Thе Whаlе, 1851";

using namespace utfcaseconv;

static void BM_utf8_ascii_lower(benchmark::State& state) {
    const char* src = ascii;
    size_t size = sizeof(ascii);
    char* dst = new char[size];
    for (auto _ : state)
    {
        tolower(src, src + size, dst);
    }
}
BENCHMARK(BM_utf8_ascii_lower);

static void BM_utf8_ascii_upper(benchmark::State& state) {
    const char* src = ascii;
    size_t size = sizeof(ascii);
    char* dst = new char[size];
    for (auto _ : state)
    {
        toupper(src, src + size, dst);
    }
}
BENCHMARK(BM_utf8_ascii_upper);

static void BM_utf8_cyrillic_lower(benchmark::State& state) {
    const char* src = cyrillic;
    size_t size = sizeof(cyrillic);
    char* dst = new char[size];
    for (auto _ : state)
    {
        tolower(src, src + size, dst);
    }
}
BENCHMARK(BM_utf8_cyrillic_lower);

static void BM_utf8_cyrillic_upper(benchmark::State& state) {
    const char* src = cyrillic;
    size_t size = sizeof(cyrillic);
    char* dst = new char[size];
    for (auto _ : state)
    {
        toupper(src, src + size, dst);
    }
}
BENCHMARK(BM_utf8_cyrillic_upper);

static void BM_utf8_mixed_lower(benchmark::State& state) {
    const char* src = mixed;
    size_t size = sizeof(mixed);
    char* dst = new char[size];
    for (auto _ : state)
    {
        tolower(src, src + size, dst);
    }
}
BENCHMARK(BM_utf8_mixed_lower);

static void BM_utf8_mixed_upper(benchmark::State& state) {
    const char* src = mixed;
    size_t size = sizeof(mixed);
    char* dst = new char[size];
    for (auto _ : state)
    {
        toupper(src, src + size, dst);
    }
}
BENCHMARK(BM_utf8_mixed_upper);

BENCHMARK_MAIN();