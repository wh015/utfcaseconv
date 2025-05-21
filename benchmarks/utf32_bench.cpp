#include <string>
#include <cstring>
#include <memory>

#include <benchmark/benchmark.h>

#include <utfcaseconv/utf32.h>

static constexpr char32_t ascii[] =
    U"Call me Ishmael. Some years ago - never mind how long precisely - having "
    U"little or no money in my purse, and nothing particular to interest me on "
    U"shore, I thought I would sail about a little and see the watery part of "
    U"the world. It is a way I have of driving off the spleen and regulating "
    U"the circulation. Whenever I find myself growing grim about the mouth; "
    U"whenever it is a damp, drizzly November in my soul; whenever I find "
    U"myself involuntarily pausing before coffin warehouses, and bringing up "
    U"the rear of every funeral I meet; and especially whenever my hypos get "
    U"such an upper hand of me, that it requires a strong moral principle to "
    U"prevent me from deliberately stepping into the street, and methodically "
    U"knocking people’s hats off - then, I account it high time to get to sea "
    U"as soon as I can. This is my substitute for pistol and ball. With a "
    U"philosophical flourish Cato throws himself upon his sword; I quietly "
    U"take to the ship. There is nothing surprising in this. If they but knew "
    U"it, almost all men in their degree, some time or other, cherish very "
    U"nearly the same feelings towards the ocean with me."
    U"There now is your insular city of the Manhattoes, belted round by "
    U"wharves as Indian isles by coral reefs - commerce surrounds it with her "
    U"surf. Right and left, the streets take you waterward. Its extreme "
    U"downtown is the battery, where that noble mole is washed by waves, and "
    U"cooled by breezes, which a few hours previous were out of sight of land. "
    U"Look at the crowds of water-gazers there."
    U"Circumambulate the city of a dreamy Sabbath afternoon. Go from Corlears "
    U"Hook to Coenties Slip, and from thence, by Whitehall, northward. What do "
    U"you see? - Posted like silent sentinels all around the town, stand "
    U"thousands upon thousands of mortal men fixed in ocean reveries. Some "
    U"leaning against the spiles; some seated upon the pier-heads; some "
    U"looking over the bulwarks of ships from China; some high aloft in the "
    U"rigging, as if striving to get a still better seaward peep. But these "
    U"are all landsmen; of week days pent up in lath and plaster - tied to "
    U"counters, nailed to benches, clinched to desks. How then is this? Are "
    U"the green fields gone? What do they here?"
    U"But look! here come more crowds, pacing straight for the water, and "
    U"seemingly bound for a dive. Strange! Nothing will content them but the "
    U"extremest limit of the land; loitering under the shady lee of yonder "
    U"warehouses will not suffice. No. They must get just as nigh the water as "
    U"they possibly can without falling in. And there they stand - miles of "
    U"them - leagues. Inlanders all, they come from lanes and alleys, streets "
    U"and avenues - north, east, south, and west. Yet here they all unite. "
    U"Tell me, does the magnetic virtue of the needles of the compasses of all "
    U"those ships attract them thither?"
    U"Once more. Say you are in the country; in some high land of lakes. Take "
    U"almost any path you please, and ten to one it carries you down in a "
    U"dale, and leaves you there by a pool in the stream. There is magic in "
    U"it. Let the most absent-minded of men be plunged in his deepest reveries "
    U"- stand that man on his legs, set his feet a-going, and he will "
    U"infallibly lead you to water, if water there be in all that region. "
    U"Should you ever be athirst in the great American desert, try this "
    U"experiment, if your caravan happen to be supplied with a metaphysical "
    U"professor. Yes, as every one knows, meditation and water are wedded for "
    U"ever."
    U"(c) Herman Melville, Moby-Dick, or The Whale, 1851";

// just a translited version of the quote above
static constexpr char32_t cyrillic[] =
    U"Цалл ме Ишмаел. Соме ыеарс аго - невер минд хов лонг прециселы - хавинг "
    U"литтле ор но монеы ин мы пурсе, анд нотхинг партицулар то интерест ме он "
    U"шоре, И тхоугхт И воулд саил абоут а литтле анд сее тхе ватеры парт оф "
    U"тхе ворлд. Ит ис а ваы И хаве оф дривинг офф тхе сплеен анд регулатинг "
    U"тхе цирцулатион. Вхеневер И финд мыселф гровинг грим абоут тхе моутх; "
    U"вхеневер ит ис а дамп, дриззлы Новембер ин мы соул; вхеневер И финд "
    U"мыселф инволунтарилы паусинг бефоре цоффин варэоусес, анд брингинг уп "
    U"тхе реар оф еверы фунерал И меет; анд еспециаллы вхеневер мы хыпос гет "
    U"суч ан уппер ханд оф ме, тхат ит реqуирес а стронг морал принципле то "
    U"превент ме фром делиберателы степпинг инто тхе стреет, анд метходицаллы "
    U"кноцкинг пеопле’с хатс офф - тхен, И аццоунт ит хигх тиме то гет то сеа "
    U"ас соон ас И цан. Тхис ис мы субституте фор пистол анд балл. Витх а "
    U"пхилосопхицал флоуриш Цато тхровс химселф упон хис сворд; И qуиетлы таке "
    U"то тхе шип. Тхере ис нотхинг сурприсинг ин тхис. Иф тхеы бут кнев ит, "
    U"алмост алл мен ин тхеир дегрее, соме тиме ор отхер, чериш веры неарлы "
    U"тхе саме феелингс товардс тхе оцеан витх ме."
    U"Тхере нов ис ёур инсулар циты оф тхе Манхаттоес, белтед роунд бы вхарвес "
    U"ас Индиан ислес бы цорал реефс - цоммерце сурроундс ит витх хер сурф. "
    U"Ригхт анд лефт, тхе стреетс таке ёу ватервард. Итс еxтреме довнтовн ис "
    U"тхе баттеры, вхере тхат нобле моле ис вашед бы вавес, анд цоолед бы "
    U"бреезес, вхич а фев хоурс превиоус вере оут оф сигхт оф ланд. Лоок ат "
    U"тхе цровдс оф ватер-газерс тхере."
    U"Цирцумамбулате тхе циты оф а дреамы Саббатх афтерноон. Го фром Цорлеарс "
    U"Хоок то Цоентиес Слип, анд фром тхенце, бы Вхитэалл, нортхвард. Вхат до "
    U"ёу сее? - Постед лике силент сентинелс алл ароунд тхе товн, станд "
    U"тхоусандс упон тхоусандс оф мортал мен фиxед ин оцеан ревериес. Соме "
    U"леанинг агаинст тхе спилес; соме сеатед упон тхе пиер-хеадс; соме "
    U"лоокинг овер тхе булваркс оф шипс фром Чина; соме хигх алофт ин тхе "
    U"риггинг, ас иф стривинг то гет а стилл беттер сеавард пееп. Бут тхесе "
    U"аре алл ландсмен; оф веек даыс пент уп ин латх анд пластер - тиед то "
    U"цоунтерс, наилед то бенчес, цлинчед то дескс. Хов тхен ис тхис? Аре тхе "
    U"греен фиелдс гоне? Вхат до тхеы хере?"
    U"Бут лоок! хере цоме море цровдс, пацинг страигхт фор тхе ватер, анд "
    U"сееминглы боунд фор а диве. Странге! Нотхинг вилл цонтент тхем бут тхе "
    U"еxтремест лимит оф тхе ланд; лоитеринг ундер тхе шады лее оф ёндер "
    U"варэоусес вилл нот суффице. Но. Тхеы муст гет юст ас нигх тхе ватер ас "
    U"тхеы поссиблы цан витхоут фаллинг ин. Анд тхере тхеы станд - милес оф "
    U"тхем - леагуес. Инландерс алл, тхеы цоме фром ланес анд аллеыс, стреетс "
    U"анд авенуес - нортх, еаст, соутх, анд вест. Ыет хере тхеы алл уните. "
    U"Телл ме, доес тхе магнетиц виртуе оф тхе неедлес оф тхе цомпассес оф алл "
    U"тхосе шипс аттрацт тхем тхитхер?"
    U"Онце море. Саы ёу аре ин тхе цоунтры; ин соме хигх ланд оф лакес. Таке "
    U"алмост аны патх ёу плеасе, анд тен то оне ит царриес ёу довн ин а дале, "
    U"анд леавес ёу тхере бы а поол ин тхе стреам. Тхере ис магиц ин ит. Лет "
    U"тхе мост абсент-миндед оф мен бе плунгед ин хис деепест ревериес - станд "
    U"тхат ман он хис легс, сет хис феет а-гоинг, анд хе вилл инфаллиблы леад "
    U"ёу то ватер, иф ватер тхере бе ин алл тхат регион. Шоулд ёу евер бе "
    U"атхирст ин тхе греат Америцан десерт, тры тхис еxперимент, иф ёур "
    U"цараван хаппен то бе супплиед витх а метапхысицал профессор. Ыес, ас "
    U"еверы оне кновс, медитатион анд ватер аре веддед фор евер."
    U"(ц) Херман Мелвилле, Мобы-Дицк, ор Тхе Вхале, 1851";

// a, o, e are replaced to cyrillic
static constexpr char32_t mixed[] =
    U"Cаll mе Ishmаеl. Sоmе yеаrs аgо - nеvеr mind hоw lоng prеcisеly - hаving "
    U"littlе оr nо mоnеy in my pursе, аnd nоthing pаrticulаr tо intеrеst mе оn "
    U"shоrе, I thоught I wоuld sаil аbоut а littlе аnd sее thе wаtеry pаrt оf "
    U"thе wоrld. It is а wаy I hаvе оf driving оff thе splееn аnd rеgulаting "
    U"thе circulаtiоn. Whеnеvеr I find mysеlf grоwing grim аbоut thе mоuth; "
    U"whеnеvеr it is а dаmp, drizzly Nоvеmbеr in my sоul; whеnеvеr I find "
    U"mysеlf invоluntаrily pаusing bеfоrе cоffin wаrеhоusеs, аnd bringing up "
    U"thе rеаr оf еvеry funеrаl I mееt; аnd еspеciаlly whеnеvеr my hypоs gеt "
    U"such аn uppеr hаnd оf mе, thаt it rеquirеs а strоng mоrаl principlе tо "
    U"prеvеnt mе frоm dеlibеrаtеly stеpping intо thе strееt, аnd mеthоdicаlly "
    U"knоcking pеоplе’s hаts оff - thеn, I аccоunt it high timе tо gеt tо sеа "
    U"аs sооn аs I cаn. This is my substitutе fоr pistоl аnd bаll. With а "
    U"philоsоphicаl flоurish Cаtо thrоws himsеlf upоn his swоrd; I quiеtly "
    U"tаkе tо thе ship. Thеrе is nоthing surprising in this. If thеy but knеw "
    U"it, аlmоst аll mеn in thеir dеgrее, sоmе timе оr оthеr, chеrish vеry "
    U"nеаrly thе sаmе fееlings tоwаrds thе оcеаn with mе."
    U"Thеrе nоw is yоur insulаr city оf thе Mаnhаttоеs, bеltеd rоund by "
    U"whаrvеs аs Indiаn islеs by cоrаl rееfs - cоmmеrcе surrоunds it with hеr "
    U"surf. Right аnd lеft, thе strееts tаkе yоu wаtеrwаrd. Its еxtrеmе "
    U"dоwntоwn is thе bаttеry, whеrе thаt nоblе mоlе is wаshеd by wаvеs, аnd "
    U"cооlеd by brееzеs, which а fеw hоurs prеviоus wеrе оut оf sight оf lаnd. "
    U"Lооk аt thе crоwds оf wаtеr-gаzеrs thеrе."
    U"Circumаmbulаtе thе city оf а drеаmy Sаbbаth аftеrnооn. Gо frоm Cоrlеаrs "
    U"Hооk tо Cоеntiеs Slip, аnd frоm thеncе, by Whitеhаll, nоrthwаrd. Whаt dо "
    U"yоu sее? - Pоstеd likе silеnt sеntinеls аll аrоund thе tоwn, stаnd "
    U"thоusаnds upоn thоusаnds оf mоrtаl mеn fixеd in оcеаn rеvеriеs. Sоmе "
    U"lеаning аgаinst thе spilеs; sоmе sеаtеd upоn thе piеr-hеаds; sоmе "
    U"lооking оvеr thе bulwаrks оf ships frоm Chinа; sоmе high аlоft in thе "
    U"rigging, аs if striving tо gеt а still bеttеr sеаwаrd pееp. But thеsе "
    U"аrе аll lаndsmеn; оf wееk dаys pеnt up in lаth аnd plаstеr - tiеd tо "
    U"cоuntеrs, nаilеd tо bеnchеs, clinchеd tо dеsks. Hоw thеn is this? аrе "
    U"thе grееn fiеlds gоnе? Whаt dо thеy hеrе?"
    U"But lооk! hеrе cоmе mоrе crоwds, pаcing strаight fоr thе wаtеr, аnd "
    U"sееmingly bоund fоr а divе. Strаngе! Nоthing will cоntеnt thеm but thе "
    U"еxtrеmеst limit оf thе lаnd; lоitеring undеr thе shаdy lее оf yоndеr "
    U"wаrеhоusеs will nоt sufficе. Nо. Thеy must gеt just аs nigh thе wаtеr аs "
    U"thеy pоssibly cаn withоut fаlling in. аnd thеrе thеy stаnd - milеs оf "
    U"thеm - lеаguеs. Inlаndеrs аll, thеy cоmе frоm lаnеs аnd аllеys, strееts "
    U"аnd аvеnuеs - nоrth, еаst, sоuth, аnd wеst. Yеt hеrе thеy аll unitе. "
    U"Tеll mе, dоеs thе mаgnеtic virtuе оf thе nееdlеs оf thе cоmpаssеs оf аll "
    U"thоsе ships аttrаct thеm thithеr?"
    U"оncе mоrе. Sаy yоu аrе in thе cоuntry; in sоmе high lаnd оf lаkеs. Tаkе "
    U"аlmоst аny pаth yоu plеаsе, аnd tеn tо оnе it cаrriеs yоu dоwn in а "
    U"dаlе, аnd lеаvеs yоu thеrе by а pооl in thе strеаm. Thеrе is mаgic in "
    U"it. Lеt thе mоst аbsеnt-mindеd оf mеn bе plungеd in his dееpеst rеvеriеs "
    U"- stаnd thаt mаn оn his lеgs, sеt his fееt а-gоing, аnd hе will "
    U"infаllibly lеаd yоu tо wаtеr, if wаtеr thеrе bе in аll thаt rеgiоn. "
    U"Shоuld yоu еvеr bе аthirst in thе grеаt аmеricаn dеsеrt, try this "
    U"еxpеrimеnt, if yоur cаrаvаn hаppеn tо bе suppliеd with а mеtаphysicаl "
    U"prоfеssоr. Yеs, аs еvеry оnе knоws, mеditаtiоn аnd wаtеr аrе wеddеd fоr "
    U"еvеr."
    U"(c) Hеrmаn Mеlvillе, Mоby-Dick, оr Thе Whаlе, 1851";

using namespace utfcaseconv::utf32;

static void BM_utf32_ascii_lower(benchmark::State& state) {
    const char32_t* src = ascii;
    size_t size = sizeof(ascii);
    auto dst = std::unique_ptr<char32_t>(new char32_t[size]);
    for (auto _ : state)
    {
        tolower(src, src + size, dst.get());
    }
}
BENCHMARK(BM_utf32_ascii_lower);

static void BM_utf32_ascii_upper(benchmark::State& state) {
    const char32_t* src = ascii;
    size_t size = sizeof(ascii);
    auto dst = std::unique_ptr<char32_t>(new char32_t[size]);
    for (auto _ : state)
    {
        toupper(src, src + size, dst.get());
    }
}
BENCHMARK(BM_utf32_ascii_upper);

static void BM_utf32_cyrillic_lower(benchmark::State& state) {
    const char32_t* src = cyrillic;
    size_t size = sizeof(cyrillic);
    auto dst = std::unique_ptr<char32_t>(new char32_t[size]);
    for (auto _ : state)
    {
        tolower(src, src + size, dst.get());
    }
}
BENCHMARK(BM_utf32_cyrillic_lower);

static void BM_utf32_cyrillic_upper(benchmark::State& state) {
    const char32_t* src = cyrillic;
    size_t size = sizeof(cyrillic);
    auto dst = std::unique_ptr<char32_t>(new char32_t[size]);
    for (auto _ : state)
    {
        toupper(src, src + size, dst.get());
    }
}
BENCHMARK(BM_utf32_cyrillic_upper);

static void BM_utf32_mixed_lower(benchmark::State& state) {
    const char32_t* src = mixed;
    size_t size = sizeof(mixed);
    auto dst = std::unique_ptr<char32_t>(new char32_t[size]);
    for (auto _ : state)
    {
        tolower(src, src + size, dst.get());
    }
}
BENCHMARK(BM_utf32_mixed_lower);

static void BM_utf32_mixed_upper(benchmark::State& state) {
    const char32_t* src = mixed;
    size_t size = sizeof(mixed);
    auto dst = std::unique_ptr<char32_t>(new char32_t[size]);
    for (auto _ : state)
    {
        toupper(src, src + size, dst.get());
    }
}
BENCHMARK(BM_utf32_mixed_upper);

BENCHMARK_MAIN();
