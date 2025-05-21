#include <string>
#include <cstring>

#include <utfcaseconv/utf32.h>

#include "catch2_wrapper.h"

static constexpr char32_t ascii[] = U"Call me Ishmael. Some years ago - never mind how long precisely - having little or no money"
    "in my purse, and nothing particular to interest me on shore, I thought I would sail about a little and see the watery part "
    "of the world. It is a way I have of driving off the spleen and regulating the circulation. Whenever I find myself growing "
    "grim about the mouth; whenever it is a damp, drizzly November in my soul; whenever I find myself involuntarily pausing "
    "before coffin warehouses, and bringing up the rear of every funeral I meet; and especially whenever my hypos get such an "
    "upper hand of me, that it requires a strong moral principle to prevent me from deliberately stepping into the street, and "
    "methodically knocking people’s hats off - then, I account it high time to get to sea as soon as I can. This is my substitute "
    "for pistol and ball. With a philosophical flourish Cato throws himself upon his sword; I quietly take to the ship. There is "
    "nothing surprising in this. If they but knew it, almost all men in their degree, some time or other, cherish very nearly the "
    "same feelings towards the ocean with me."
    "There now is your insular city of the Manhattoes, belted round by wharves as Indian isles by coral reefs - commerce surrounds "
    "it with her surf. Right and left, the streets take you waterward. Its extreme downtown is the battery, where that noble mole is "
    "washed by waves, and cooled by breezes, which a few hours previous were out of sight of land. Look at the crowds of water-gazers "
    "there."
    "Circumambulate the city of a dreamy Sabbath afternoon. Go from Corlears Hook to Coenties Slip, and from thence, by Whitehall, "
    "northward. What do you see? - Posted like silent sentinels all around the town, stand thousands upon thousands of mortal men "
    "fixed in ocean reveries. Some leaning against the spiles; some seated upon the pier-heads; some looking over the bulwarks of "
    "ships from China; some high aloft in the rigging, as if striving to get a still better seaward peep. But these are all landsmen; "
    "of week days pent up in lath and plaster - tied to counters, nailed to benches, clinched to desks. How then is this? Are the "
    "green fields gone? What do they here?"
    "(c) Herman Melville, Moby-Dick, or The Whale, 1851";

// just a translited version of the quote above
static constexpr char32_t cyrillic[] = U"Цалл ме Ишмаел. Соме ыеарс аго - невер минд хов лонг прециселы - хавинг литтле ор но монеы"
    "ин мы пурсе, анд нотхинг партицулар то интерест ме он шоре, И тхоугхт И воулд саил абоут а литтле анд сее тхе ватеры парт "
    "оф тхе ворлд. Ит ис а ваы И хаве оф дривинг офф тхе сплеен анд регулатинг тхе цирцулатион. Вхеневер И финд мыселф гровинг "
    "грим абоут тхе моутх; вхеневер ит ис а дамп, дриззлы Новембер ин мы соул; вхеневер И финд мыселф инволунтарилы паусинг "
    "бефоре цоффин варэоусес, анд брингинг уп тхе реар оф еверы фунерал И меет; анд еспециаллы вхеневер мы хыпос гет суч ан "
    "уппер ханд оф ме, тхат ит реqуирес а стронг морал принципле то превент ме фром делиберателы степпинг инто тхе стреет, анд "
    "метходицаллы кноцкинг пеопле’с хатс офф - тхен, И аццоунт ит хигх тиме то гет то сеа ас соон ас И цан. Тхис ис мы субституте "
    "фор пистол анд балл. Витх а пхилосопхицал флоуриш Цато тхровс химселф упон хис сворд; И qуиетлы таке то тхе шип. Тхере ис "
    "нотхинг сурприсинг ин тхис. Иф тхеы бут кнев ит, алмост алл мен ин тхеир дегрее, соме тиме ор отхер, чериш веры неарлы тхе "
    "саме феелингс товардс тхе оцеан витх ме."
    "Тхере нов ис ёур инсулар циты оф тхе Манхаттоес, белтед роунд бы вхарвес ас Индиан ислес бы цорал реефс - цоммерце сурроундс "
    "ит витх хер сурф. Ригхт анд лефт, тхе стреетс таке ёу ватервард. Итс еxтреме довнтовн ис тхе баттеры, вхере тхат нобле моле ис "
    "вашед бы вавес, анд цоолед бы бреезес, вхич а фев хоурс превиоус вере оут оф сигхт оф ланд. Лоок ат тхе цровдс оф ватер-газерс "
    "тхере."
    "Цирцумамбулате тхе циты оф а дреамы Саббатх афтерноон. Го фром Цорлеарс Хоок то Цоентиес Слип, анд фром тхенце, бы Вхитэалл, "
    "нортхвард. Вхат до ёу сее? - Постед лике силент сентинелс алл ароунд тхе товн, станд тхоусандс упон тхоусандс оф мортал мен "
    "фиxед ин оцеан ревериес. Соме леанинг агаинст тхе спилес; соме сеатед упон тхе пиер-хеадс; соме лоокинг овер тхе булваркс оф "
    "шипс фром Чина; соме хигх алофт ин тхе риггинг, ас иф стривинг то гет а стилл беттер сеавард пееп. Бут тхесе аре алл ландсмен; "
    "оф веек даыс пент уп ин латх анд пластер - тиед то цоунтерс, наилед то бенчес, цлинчед то дескс. Хов тхен ис тхис? Аре тхе "
    "греен фиелдс гоне? Вхат до тхеы хере?"
    "(ц) Херман Мелвилле, Мобы-Дицк, ор Тхе Вхале, 1851";

// a, o, e are replaced to cyrillic
static constexpr char32_t mixed[] = U"Cаll mе Ishmаеl. Sоmе yеаrs аgо - nеvеr mind hоw lоng prеcisеly - hаving littlе оr nо mоnеy"
    "in my pursе, аnd nоthing pаrticulаr tо intеrеst mе оn shоrе, I thоught I wоuld sаil аbоut а littlе аnd sее thе wаtеry pаrt "
    "оf thе wоrld. It is а wаy I hаvе оf driving оff thе splееn аnd rеgulаting thе circulаtiоn. Whеnеvеr I find mysеlf grоwing "
    "grim аbоut thе mоuth; whеnеvеr it is а dаmp, drizzly Nоvеmbеr in my sоul; whеnеvеr I find mysеlf invоluntаrily pаusing "
    "bеfоrе cоffin wаrеhоusеs, аnd bringing up thе rеаr оf еvеry funеrаl I mееt; аnd еspеciаlly whеnеvеr my hypоs gеt such аn "
    "uppеr hаnd оf mе, thаt it rеquirеs а strоng mоrаl principlе tо prеvеnt mе frоm dеlibеrаtеly stеpping intо thе strееt, аnd "
    "mеthоdicаlly knоcking pеоplе’s hаts оff - thеn, I аccоunt it high timе tо gеt tо sеа аs sооn аs I cаn. This is my substitutе "
    "fоr pistоl аnd bаll. With а philоsоphicаl flоurish Cаtо thrоws himsеlf upоn his swоrd; I quiеtly tаkе tо thе ship. Thеrе is "
    "nоthing surprising in this. If thеy but knеw it, аlmоst аll mеn in thеir dеgrее, sоmе timе оr оthеr, chеrish vеry nеаrly thе "
    "sаmе fееlings tоwаrds thе оcеаn with mе."
    "Thеrе nоw is yоur insulаr city оf thе Mаnhаttоеs, bеltеd rоund by whаrvеs аs Indiаn islеs by cоrаl rееfs - cоmmеrcе surrоunds "
    "it with hеr surf. Right аnd lеft, thе strееts tаkе yоu wаtеrwаrd. Its еxtrеmе dоwntоwn is thе bаttеry, whеrе thаt nоblе mоlе is "
    "wаshеd by wаvеs, аnd cооlеd by brееzеs, which а fеw hоurs prеviоus wеrе оut оf sight оf lаnd. Lооk аt thе crоwds оf wаtеr-gаzеrs "
    "thеrе."
    "Circumаmbulаtе thе city оf а drеаmy Sаbbаth аftеrnооn. Gо frоm Cоrlеаrs Hооk tо Cоеntiеs Slip, аnd frоm thеncе, by Whitеhаll, "
    "nоrthwаrd. Whаt dо yоu sее? - Pоstеd likе silеnt sеntinеls аll аrоund thе tоwn, stаnd thоusаnds upоn thоusаnds оf mоrtаl mеn "
    "fixеd in оcеаn rеvеriеs. Sоmе lеаning аgаinst thе spilеs; sоmе sеаtеd upоn thе piеr-hеаds; sоmе lооking оvеr thе bulwаrks оf "
    "ships frоm Chinа; sоmе high аlоft in thе rigging, аs if striving tо gеt а still bеttеr sеаwаrd pееp. But thеsе аrе аll lаndsmеn; "
    "оf wееk dаys pеnt up in lаth аnd plаstеr - tiеd tо cоuntеrs, nаilеd tо bеnchеs, clinchеd tо dеsks. Hоw thеn is this? аrе thе "
    "grееn fiеlds gоnе? Whаt dо thеy hеrе?"
    "(c) Hеrmаn Mеlvillе, Mоby-Dick, оr Thе Whаlе, 1851";

using namespace utfcaseconv::utf32;

TEST_CASE("UTF-32 ASCII") {
    const char32_t *src = ascii;
    size_t size = sizeof(ascii);
    char32_t *dst = new char32_t[size];

    BENCHMARK("ASCII to upper") {
        return toupper(src, src + size, dst);
    };

    BENCHMARK("ASCII to lower") {
        return toupper(src, src + size, dst);
    };

    delete dst;
}

TEST_CASE("UTF-32 Cyrllic") {
    const char32_t *src = cyrillic;
    size_t size = sizeof(cyrillic);
    char32_t *dst = new char32_t[size];

    BENCHMARK("Cyrllic to upper") {
        return toupper(src, src + size, dst);
    };

    BENCHMARK("Cyrllic to lower") {
        return tolower(src, src + size, dst);
    };

    delete dst;
}

TEST_CASE("UTF-32 Mixed") {
    const char32_t *src = mixed;
    size_t size = sizeof(mixed);
    char32_t *dst = new char32_t[size];

    BENCHMARK("Mixed to upper") {
        return toupper(src, src + size, dst);
    };

    BENCHMARK("Mixed to lower") {
        return tolower(src, src + size, dst);
    };

    delete dst;
}
