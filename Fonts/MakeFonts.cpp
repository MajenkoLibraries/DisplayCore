
#include "Acorn8x8/Acorn8x8.h"
#include "Acorn/Acorn.h"
#include "Aquarius/Aquarius.h"
#include "Arial/Arial.h"
#include "ArialBold/ArialBold.h"
#include "Atari/Atari.h"
#include "AtariButtons/AtariButtons.h"
#include "AVOP/AVOP.h"
#include "Bisasam/Bisasam.h"
#include "BPMonoItalic/BPMonoItalic.h"
#include "BunnyMambo/BunnyMambo.h"
#include "Carbine/Carbine.h"
#include "ComfortAA/ComfortAA.h"
#include "Comic/Comic.h"
#include "CP111/CP111.h"
#include "CP112/CP112.h"
#include "CP113/CP113.h"
#include "CP437/CP437.h"
#include "CP737/CP737.h"
#include "CP850/CP850.h"
#include "CP851/CP851.h"
#include "CP852/CP852.h"
#include "CP853/CP853.h"
#include "CP860/CP860.h"
#include "CP861/CP861.h"
#include "CP862/CP862.h"
#include "CP863/CP863.h"
#include "CP864/CP864.h"
#include "CP865/CP865.h"
#include "CP866/CP866.h"
#include "CP880/CP880.h"
#include "CP881/CP881.h"
#include "CP882/CP882.h"
#include "CP883/CP883.h"
#include "CP884/CP884.h"
#include "CP885/CP885.h"
#include "DejaVuSans/DejaVuSans.h"
#include "DejaVuSansMono/DejaVuSansMono.h"
#include "Display7Seg/Display7Seg.h"
#include "Display7SegShadow/Display7SegShadow.h"
#include "Doorly/Doorly.h"
#include "DOS/DOS.h"
#include "EngliBesh/EngliBesh.h"
#include "Font44/Font44.h"
#include "Gem/Gem.h"
#include "GeorgiaBoldItalic/GeorgiaBoldItalic.h"
#include "Hazard/Hazard.h"
#include "Icon8/Icon8.h"
#include "Ingot/Ingot.h"
#include "Kimberley/Kimberley.h"
#include "LCARS/LCARS.h"
#include "LCDish/LCDish.h"
#include "LedMatrixBright/LedMatrixBright.h"
#include "LedMatrixDim/LedMatrixDim.h"
#include "Liberation/Liberation.h"
#include "Linux10x18/Linux10x18.h"
#include "Linux6x10/Linux6x10.h"
#include "Linux7x14/Linux7x14.h"
#include "MINI4x6/MINI4x6.h"
#include "OCRAExtended/OCRAExtended.h"
#include "OldStandard/OldStandard.h"
#include "Open24Display/Open24Display.h"
#include "PEARL8x8/PEARL8x8.h"
#include "ProFont6x11/ProFont6x11.h"
#include "RawGold/RawGold.h"
#include "Roboto/Roboto.h"
#include "SheepSans/SheepSans.h"
#include "Sinclair/Sinclair.h"
#include "Squircle/Squircle.h"
#include "SUN12x22/SUN12x22.h"
#include "SUN8x16/SUN8x16.h"
#include "Terminus6x12/Terminus6x12.h"
#include "Topaz/Topaz.h"
#include "Ubuntu/Ubuntu.h"
#include "Unicode/Unicode.h"
#include "VGA8x16/VGA8x16.h"
#include "VGA8x8/VGA8x8.h"
#include "XTerm/XTerm.h"
#include "Clive/Clive.h"
#include "Pipes/Pipes.h"

extern void makeFont(const char *family, const char *name, const uint8_t *data);

void makeFonts() {
    makeFont("Acorn8x8", "Acorn8x8", Fonts::Acorn8x8);
    makeFont("Acorn", "Acorn", Fonts::Acorn);
    makeFont("Aquarius", "Aquarius", Fonts::Aquarius);
    makeFont("Arial", "Arial10", Fonts::Arial10);
    makeFont("Arial", "Arial12", Fonts::Arial12);
    makeFont("Arial", "Arial14", Fonts::Arial14);
    makeFont("Arial", "Arial16", Fonts::Arial16);
    makeFont("Arial", "Arial18", Fonts::Arial18);
    makeFont("Arial", "Arial20", Fonts::Arial20);
    makeFont("Arial", "Arial22", Fonts::Arial22);
    makeFont("Arial", "Arial24", Fonts::Arial24);
    makeFont("Arial", "Arial26", Fonts::Arial26);
    makeFont("Arial", "Arial28", Fonts::Arial28);
    makeFont("Arial", "Arial30", Fonts::Arial30);
    makeFont("Arial", "Arial32", Fonts::Arial32);
    makeFont("Arial", "Arial34", Fonts::Arial34);
    makeFont("Arial", "Arial36", Fonts::Arial36);
    makeFont("Arial", "Arial38", Fonts::Arial38);
    makeFont("Arial", "Arial40", Fonts::Arial40);
    makeFont("Arial", "Arial8", Fonts::Arial8);
    makeFont("ArialBold", "ArialBold10", Fonts::ArialBold10);
    makeFont("ArialBold", "ArialBold12", Fonts::ArialBold12);
    makeFont("ArialBold", "ArialBold14", Fonts::ArialBold14);
    makeFont("ArialBold", "ArialBold16", Fonts::ArialBold16);
    makeFont("ArialBold", "ArialBold18", Fonts::ArialBold18);
    makeFont("ArialBold", "ArialBold20", Fonts::ArialBold20);
    makeFont("ArialBold", "ArialBold22", Fonts::ArialBold22);
    makeFont("ArialBold", "ArialBold24", Fonts::ArialBold24);
    makeFont("ArialBold", "ArialBold26", Fonts::ArialBold26);
    makeFont("ArialBold", "ArialBold28", Fonts::ArialBold28);
    makeFont("ArialBold", "ArialBold30", Fonts::ArialBold30);
    makeFont("ArialBold", "ArialBold32", Fonts::ArialBold32);
    makeFont("ArialBold", "ArialBold34", Fonts::ArialBold34);
    makeFont("ArialBold", "ArialBold36", Fonts::ArialBold36);
    makeFont("ArialBold", "ArialBold38", Fonts::ArialBold38);
    makeFont("ArialBold", "ArialBold40", Fonts::ArialBold40);
    makeFont("ArialBold", "ArialBold8", Fonts::ArialBold8);
    makeFont("Atari", "Atari", Fonts::Atari);
    makeFont("AtariButtons", "AtariButtons", Fonts::AtariButtons);
    makeFont("AVOP", "AVOP", Fonts::AVOP);
    makeFont("Bisasam", "Bisasam", Fonts::Bisasam);
    makeFont("BPMonoItalic", "BPMonoItalic20", Fonts::BPMonoItalic20);
    makeFont("BPMonoItalic", "BPMonoItalic22", Fonts::BPMonoItalic22);
    makeFont("BPMonoItalic", "BPMonoItalic24", Fonts::BPMonoItalic24);
    makeFont("BPMonoItalic", "BPMonoItalic26", Fonts::BPMonoItalic26);
    makeFont("BPMonoItalic", "BPMonoItalic28", Fonts::BPMonoItalic28);
    makeFont("BPMonoItalic", "BPMonoItalic30", Fonts::BPMonoItalic30);
    makeFont("BPMonoItalic", "BPMonoItalic32", Fonts::BPMonoItalic32);
    makeFont("BPMonoItalic", "BPMonoItalic34", Fonts::BPMonoItalic34);
    makeFont("BPMonoItalic", "BPMonoItalic36", Fonts::BPMonoItalic36);
    makeFont("BPMonoItalic", "BPMonoItalic38", Fonts::BPMonoItalic38);
    makeFont("BPMonoItalic", "BPMonoItalic40", Fonts::BPMonoItalic40);
    makeFont("BPMonoItalic", "BPMonoItalic18", Fonts::BPMonoItalic18);
    makeFont("BunnyMambo", "BunnyMambo60", Fonts::BunnyMambo60);
    makeFont("Carbine", "Carbine", Fonts::Carbine);
    makeFont("ComfortAA", "ComfortAA8", Fonts::ComfortAA8);
    makeFont("ComfortAA", "ComfortAA10", Fonts::ComfortAA10);
    makeFont("ComfortAA", "ComfortAA12", Fonts::ComfortAA12);
    makeFont("ComfortAA", "ComfortAA14", Fonts::ComfortAA14);
    makeFont("ComfortAA", "ComfortAA16", Fonts::ComfortAA16);
    makeFont("ComfortAA", "ComfortAA18", Fonts::ComfortAA18);
    makeFont("ComfortAA", "ComfortAA20", Fonts::ComfortAA20);
    makeFont("ComfortAA", "ComfortAA22", Fonts::ComfortAA22);
    makeFont("ComfortAA", "ComfortAA24", Fonts::ComfortAA24);
    makeFont("ComfortAA", "ComfortAA26", Fonts::ComfortAA26);
    makeFont("ComfortAA", "ComfortAA28", Fonts::ComfortAA28);
    makeFont("ComfortAA", "ComfortAA30", Fonts::ComfortAA30);
    makeFont("Comic", "Comic", Fonts::Comic);
    makeFont("CP111", "CP111", Fonts::CP111);
    makeFont("CP112", "CP112", Fonts::CP112);
    makeFont("CP113", "CP113", Fonts::CP113);
    makeFont("CP437", "CP437", Fonts::CP437);
    makeFont("CP737", "CP737", Fonts::CP737);
    makeFont("CP850", "CP850", Fonts::CP850);
    makeFont("CP851", "CP851", Fonts::CP851);
    makeFont("CP852", "CP852", Fonts::CP852);
    makeFont("CP853", "CP853", Fonts::CP853);
    makeFont("CP860", "CP860", Fonts::CP860);
    makeFont("CP861", "CP861", Fonts::CP861);
    makeFont("CP862", "CP862", Fonts::CP862);
    makeFont("CP863", "CP863", Fonts::CP863);
    makeFont("CP864", "CP864", Fonts::CP864);
    makeFont("CP865", "CP865", Fonts::CP865);
    makeFont("CP866", "CP866", Fonts::CP866);
    makeFont("CP880", "CP880", Fonts::CP880);
    makeFont("CP881", "CP881", Fonts::CP881);
    makeFont("CP882", "CP882", Fonts::CP882);
    makeFont("CP883", "CP883", Fonts::CP883);
    makeFont("CP884", "CP884", Fonts::CP884);
    makeFont("CP885", "CP885", Fonts::CP885);
    makeFont("DejaVuSans", "DejaVuSans8", Fonts::DejaVuSans8);
    makeFont("DejaVuSans", "DejaVuSans9", Fonts::DejaVuSans9);
    makeFont("DejaVuSans", "DejaVuSans10", Fonts::DejaVuSans10);
    makeFont("DejaVuSans", "DejaVuSans11", Fonts::DejaVuSans11);
    makeFont("DejaVuSans", "DejaVuSans12", Fonts::DejaVuSans12);
    makeFont("DejaVuSans", "DejaVuSans13", Fonts::DejaVuSans13);
    makeFont("DejaVuSans", "DejaVuSans14", Fonts::DejaVuSans14);
    makeFont("DejaVuSans", "DejaVuSans15", Fonts::DejaVuSans15);
    makeFont("DejaVuSans", "DejaVuSans16", Fonts::DejaVuSans16);
    makeFont("DejaVuSans", "DejaVuSans17", Fonts::DejaVuSans17);
    makeFont("DejaVuSans", "DejaVuSans18", Fonts::DejaVuSans18);
    makeFont("DejaVuSans", "DejaVuSans19", Fonts::DejaVuSans19);
    makeFont("DejaVuSans", "DejaVuSans20", Fonts::DejaVuSans20);
    makeFont("DejaVuSans", "DejaVuSans21", Fonts::DejaVuSans21);
    makeFont("DejaVuSans", "DejaVuSans22", Fonts::DejaVuSans22);
    makeFont("DejaVuSans", "DejaVuSans23", Fonts::DejaVuSans23);
    makeFont("DejaVuSans", "DejaVuSans24", Fonts::DejaVuSans24);
    makeFont("DejaVuSans", "DejaVuSans25", Fonts::DejaVuSans25);
    makeFont("DejaVuSans", "DejaVuSans26", Fonts::DejaVuSans26);
    makeFont("DejaVuSans", "DejaVuSans27", Fonts::DejaVuSans27);
    makeFont("DejaVuSans", "DejaVuSans28", Fonts::DejaVuSans28);
    makeFont("DejaVuSans", "DejaVuSans29", Fonts::DejaVuSans29);
    makeFont("DejaVuSans", "DejaVuSans30", Fonts::DejaVuSans30);
    makeFont("DejaVuSans", "DejaVuSans31", Fonts::DejaVuSans31);
    makeFont("DejaVuSans", "DejaVuSans32", Fonts::DejaVuSans32);
    makeFont("DejaVuSans", "DejaVuSans33", Fonts::DejaVuSans33);
    makeFont("DejaVuSans", "DejaVuSans34", Fonts::DejaVuSans34);
    makeFont("DejaVuSans", "DejaVuSans35", Fonts::DejaVuSans35);
    makeFont("DejaVuSans", "DejaVuSans36", Fonts::DejaVuSans36);
    makeFont("DejaVuSans", "DejaVuSans37", Fonts::DejaVuSans37);
    makeFont("DejaVuSansMono", "DejaVuSansMono8", Fonts::DejaVuSansMono8);
    makeFont("DejaVuSansMono", "DejaVuSansMono9", Fonts::DejaVuSansMono9);
    makeFont("DejaVuSansMono", "DejaVuSansMono10", Fonts::DejaVuSansMono10);
    makeFont("DejaVuSansMono", "DejaVuSansMono11", Fonts::DejaVuSansMono11);
    makeFont("DejaVuSansMono", "DejaVuSansMono12", Fonts::DejaVuSansMono12);
    makeFont("DejaVuSansMono", "DejaVuSansMono13", Fonts::DejaVuSansMono13);
    makeFont("DejaVuSansMono", "DejaVuSansMono14", Fonts::DejaVuSansMono14);
    makeFont("DejaVuSansMono", "DejaVuSansMono15", Fonts::DejaVuSansMono15);
    makeFont("DejaVuSansMono", "DejaVuSansMono16", Fonts::DejaVuSansMono16);
    makeFont("DejaVuSansMono", "DejaVuSansMono17", Fonts::DejaVuSansMono17);
    makeFont("DejaVuSansMono", "DejaVuSansMono18", Fonts::DejaVuSansMono18);
    makeFont("DejaVuSansMono", "DejaVuSansMono19", Fonts::DejaVuSansMono19);
    makeFont("DejaVuSansMono", "DejaVuSansMono20", Fonts::DejaVuSansMono20);
    makeFont("DejaVuSansMono", "DejaVuSansMono21", Fonts::DejaVuSansMono21);
    makeFont("DejaVuSansMono", "DejaVuSansMono22", Fonts::DejaVuSansMono22);
    makeFont("DejaVuSansMono", "DejaVuSansMono23", Fonts::DejaVuSansMono23);
    makeFont("DejaVuSansMono", "DejaVuSansMono24", Fonts::DejaVuSansMono24);
    makeFont("DejaVuSansMono", "DejaVuSansMono25", Fonts::DejaVuSansMono25);
    makeFont("DejaVuSansMono", "DejaVuSansMono26", Fonts::DejaVuSansMono26);
    makeFont("DejaVuSansMono", "DejaVuSansMono27", Fonts::DejaVuSansMono27);
    makeFont("DejaVuSansMono", "DejaVuSansMono28", Fonts::DejaVuSansMono28);
    makeFont("DejaVuSansMono", "DejaVuSansMono29", Fonts::DejaVuSansMono29);
    makeFont("DejaVuSansMono", "DejaVuSansMono30", Fonts::DejaVuSansMono30);
    makeFont("DejaVuSansMono", "DejaVuSansMono31", Fonts::DejaVuSansMono31);
    makeFont("DejaVuSansMono", "DejaVuSansMono32", Fonts::DejaVuSansMono32);
    makeFont("DejaVuSansMono", "DejaVuSansMono33", Fonts::DejaVuSansMono33);
    makeFont("DejaVuSansMono", "DejaVuSansMono34", Fonts::DejaVuSansMono34);
    makeFont("DejaVuSansMono", "DejaVuSansMono35", Fonts::DejaVuSansMono35);
    makeFont("DejaVuSansMono", "DejaVuSansMono36", Fonts::DejaVuSansMono36);
    makeFont("DejaVuSansMono", "DejaVuSansMono37", Fonts::DejaVuSansMono37);
    makeFont("Display7Seg", "Display7Seg32", Fonts::Display7Seg32);
    makeFont("Display7Seg", "Display7Seg48", Fonts::Display7Seg48);
    makeFont("Display7SegShadow", "Display7SegShadow32", Fonts::Display7SegShadow32);
    makeFont("Display7SegShadow", "Display7SegShadow48", Fonts::Display7SegShadow48);
    makeFont("Doorly", "Doorly", Fonts::Doorly);
    makeFont("DOS", "DOS", Fonts::DOS);
    makeFont("EngliBesh", "EngliBesh8", Fonts::EngliBesh8);
    makeFont("EngliBesh", "EngliBesh9", Fonts::EngliBesh9);
    makeFont("EngliBesh", "EngliBesh10", Fonts::EngliBesh10);
    makeFont("EngliBesh", "EngliBesh11", Fonts::EngliBesh11);
    makeFont("EngliBesh", "EngliBesh12", Fonts::EngliBesh12);
    makeFont("EngliBesh", "EngliBesh13", Fonts::EngliBesh13);
    makeFont("EngliBesh", "EngliBesh14", Fonts::EngliBesh14);
    makeFont("EngliBesh", "EngliBesh15", Fonts::EngliBesh15);
    makeFont("EngliBesh", "EngliBesh16", Fonts::EngliBesh16);
    makeFont("EngliBesh", "EngliBesh17", Fonts::EngliBesh17);
    makeFont("EngliBesh", "EngliBesh18", Fonts::EngliBesh18);
    makeFont("EngliBesh", "EngliBesh19", Fonts::EngliBesh19);
    makeFont("EngliBesh", "EngliBesh20", Fonts::EngliBesh20);
    makeFont("EngliBesh", "EngliBesh21", Fonts::EngliBesh21);
    makeFont("EngliBesh", "EngliBesh22", Fonts::EngliBesh22);
    makeFont("EngliBesh", "EngliBesh23", Fonts::EngliBesh23);
    makeFont("EngliBesh", "EngliBesh24", Fonts::EngliBesh24);
    makeFont("EngliBesh", "EngliBesh25", Fonts::EngliBesh25);
    makeFont("EngliBesh", "EngliBesh26", Fonts::EngliBesh26);
    makeFont("EngliBesh", "EngliBesh27", Fonts::EngliBesh27);
    makeFont("EngliBesh", "EngliBesh28", Fonts::EngliBesh28);
    makeFont("EngliBesh", "EngliBesh29", Fonts::EngliBesh29);
    makeFont("EngliBesh", "EngliBesh30", Fonts::EngliBesh30);
    makeFont("EngliBesh", "EngliBesh31", Fonts::EngliBesh31);
    makeFont("EngliBesh", "EngliBesh32", Fonts::EngliBesh32);
    makeFont("EngliBesh", "EngliBesh33", Fonts::EngliBesh33);
    makeFont("EngliBesh", "EngliBesh34", Fonts::EngliBesh34);
    makeFont("EngliBesh", "EngliBesh35", Fonts::EngliBesh35);
    makeFont("EngliBesh", "EngliBesh36", Fonts::EngliBesh36);
    makeFont("EngliBesh", "EngliBesh37", Fonts::EngliBesh37);
    makeFont("EngliBesh", "EngliBesh38", Fonts::EngliBesh38);
    makeFont("EngliBesh", "EngliBesh39", Fonts::EngliBesh39);
    makeFont("EngliBesh", "EngliBesh40", Fonts::EngliBesh40);
    makeFont("Font44", "Font44", Fonts::Font44);
    makeFont("Gem", "Gem", Fonts::Gem);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic8", Fonts::GeorgiaBoldItalic8);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic10", Fonts::GeorgiaBoldItalic10);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic12", Fonts::GeorgiaBoldItalic12);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic14", Fonts::GeorgiaBoldItalic14);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic16", Fonts::GeorgiaBoldItalic16);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic18", Fonts::GeorgiaBoldItalic18);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic20", Fonts::GeorgiaBoldItalic20);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic22", Fonts::GeorgiaBoldItalic22);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic24", Fonts::GeorgiaBoldItalic24);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic26", Fonts::GeorgiaBoldItalic26);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic28", Fonts::GeorgiaBoldItalic28);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic30", Fonts::GeorgiaBoldItalic30);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic32", Fonts::GeorgiaBoldItalic32);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic34", Fonts::GeorgiaBoldItalic34);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic36", Fonts::GeorgiaBoldItalic36);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic38", Fonts::GeorgiaBoldItalic38);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic40", Fonts::GeorgiaBoldItalic40);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic42", Fonts::GeorgiaBoldItalic42);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic44", Fonts::GeorgiaBoldItalic44);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic46", Fonts::GeorgiaBoldItalic46);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic48", Fonts::GeorgiaBoldItalic48);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic50", Fonts::GeorgiaBoldItalic50);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic52", Fonts::GeorgiaBoldItalic52);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic54", Fonts::GeorgiaBoldItalic54);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic56", Fonts::GeorgiaBoldItalic56);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic58", Fonts::GeorgiaBoldItalic58);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic60", Fonts::GeorgiaBoldItalic60);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic62", Fonts::GeorgiaBoldItalic62);
    makeFont("GeorgiaBoldItalic", "GeorgiaBoldItalic64", Fonts::GeorgiaBoldItalic64);
    makeFont("Hazard", "Hazard10", Fonts::Hazard10);
    makeFont("Hazard", "Hazard12", Fonts::Hazard12);
    makeFont("Hazard", "Hazard14", Fonts::Hazard14);
    makeFont("Hazard", "Hazard16", Fonts::Hazard16);
    makeFont("Hazard", "Hazard40", Fonts::Hazard40);
    makeFont("Hazard", "Hazard60", Fonts::Hazard60);
    makeFont("Icon8", "Icon8", Fonts::Icon8);
    makeFont("Ingot", "Ingot", Fonts::Ingot);
    makeFont("Kimberley", "Kimberley8", Fonts::Kimberley8);
    makeFont("Kimberley", "Kimberley9", Fonts::Kimberley9);
    makeFont("Kimberley", "Kimberley10", Fonts::Kimberley10);
    makeFont("Kimberley", "Kimberley11", Fonts::Kimberley11);
    makeFont("Kimberley", "Kimberley12", Fonts::Kimberley12);
    makeFont("Kimberley", "Kimberley13", Fonts::Kimberley13);
    makeFont("Kimberley", "Kimberley14", Fonts::Kimberley14);
    makeFont("Kimberley", "Kimberley15", Fonts::Kimberley15);
    makeFont("Kimberley", "Kimberley16", Fonts::Kimberley16);
    makeFont("Kimberley", "Kimberley17", Fonts::Kimberley17);
    makeFont("Kimberley", "Kimberley18", Fonts::Kimberley18);
    makeFont("Kimberley", "Kimberley19", Fonts::Kimberley19);
    makeFont("Kimberley", "Kimberley20", Fonts::Kimberley20);
    makeFont("Kimberley", "Kimberley21", Fonts::Kimberley21);
    makeFont("Kimberley", "Kimberley22", Fonts::Kimberley22);
    makeFont("Kimberley", "Kimberley23", Fonts::Kimberley23);
    makeFont("Kimberley", "Kimberley24", Fonts::Kimberley24);
    makeFont("Kimberley", "Kimberley25", Fonts::Kimberley25);
    makeFont("Kimberley", "Kimberley26", Fonts::Kimberley26);
    makeFont("Kimberley", "Kimberley27", Fonts::Kimberley27);
    makeFont("Kimberley", "Kimberley28", Fonts::Kimberley28);
    makeFont("Kimberley", "Kimberley29", Fonts::Kimberley29);
    makeFont("Kimberley", "Kimberley30", Fonts::Kimberley30);
    makeFont("Kimberley", "Kimberley31", Fonts::Kimberley31);
    makeFont("Kimberley", "Kimberley32", Fonts::Kimberley32);
    makeFont("Kimberley", "Kimberley33", Fonts::Kimberley33);
    makeFont("Kimberley", "Kimberley34", Fonts::Kimberley34);
    makeFont("Kimberley", "Kimberley35", Fonts::Kimberley35);
    makeFont("Kimberley", "Kimberley36", Fonts::Kimberley36);
    makeFont("Kimberley", "Kimberley37", Fonts::Kimberley37);
    makeFont("Kimberley", "Kimberley38", Fonts::Kimberley38);
    makeFont("Kimberley", "Kimberley39", Fonts::Kimberley39);
    makeFont("Kimberley", "Kimberley40", Fonts::Kimberley40);
    makeFont("LCARS", "LCARS8", Fonts::LCARS8);
    makeFont("LCARS", "LCARS10", Fonts::LCARS10);
    makeFont("LCARS", "LCARS12", Fonts::LCARS12);
    makeFont("LCARS", "LCARS14", Fonts::LCARS14);
    makeFont("LCARS", "LCARS16", Fonts::LCARS16);
    makeFont("LCARS", "LCARS18", Fonts::LCARS18);
    makeFont("LCARS", "LCARS20", Fonts::LCARS20);
    makeFont("LCARS", "LCARS22", Fonts::LCARS22);
    makeFont("LCARS", "LCARS24", Fonts::LCARS24);
    makeFont("LCARS", "LCARS26", Fonts::LCARS26);
    makeFont("LCARS", "LCARS28", Fonts::LCARS28);
    makeFont("LCARS", "LCARS30", Fonts::LCARS30);
    makeFont("LCARS", "LCARS32", Fonts::LCARS32);
    makeFont("LCARS", "LCARS34", Fonts::LCARS34);
    makeFont("LCARS", "LCARS36", Fonts::LCARS36);
    makeFont("LCARS", "LCARS38", Fonts::LCARS38);
    makeFont("LCARS", "LCARS40", Fonts::LCARS40);
    makeFont("LCDish", "LCDish", Fonts::LCDish);
    makeFont("LedMatrixBright", "LedMatrixBright", Fonts::LedMatrixBright);
    makeFont("LedMatrixDim", "LedMatrixDim", Fonts::LedMatrixDim);
    makeFont("Liberation", "Liberation10", Fonts::Liberation10);
    makeFont("Liberation", "Liberation12", Fonts::Liberation12);
    makeFont("Liberation", "Liberation14", Fonts::Liberation14);
    makeFont("Liberation", "Liberation16", Fonts::Liberation16);
    makeFont("Liberation", "Liberation18", Fonts::Liberation18);
    makeFont("Liberation", "Liberation20", Fonts::Liberation20);
    makeFont("Liberation", "Liberation22", Fonts::Liberation22);
    makeFont("Liberation", "Liberation24", Fonts::Liberation24);
    makeFont("Liberation", "Liberation26", Fonts::Liberation26);
    makeFont("Liberation", "Liberation28", Fonts::Liberation28);
    makeFont("Liberation", "Liberation30", Fonts::Liberation30);
    makeFont("Liberation", "Liberation32", Fonts::Liberation32);
    makeFont("Liberation", "Liberation34", Fonts::Liberation34);
    makeFont("Liberation", "Liberation36", Fonts::Liberation36);
    makeFont("Liberation", "Liberation8", Fonts::Liberation8);
    makeFont("Linux10x18", "Linux10x18", Fonts::Linux10x18);
    makeFont("Linux6x10", "Linux6x10", Fonts::Linux6x10);
    makeFont("Linux7x14", "Linux7x14", Fonts::Linux7x14);
    makeFont("MINI4x6", "MINI4x6", Fonts::MINI4x6);
    makeFont("OCRAExtended", "OCRAExtended8", Fonts::OCRAExtended8);
    makeFont("OCRAExtended", "OCRAExtended9", Fonts::OCRAExtended9);
    makeFont("OCRAExtended", "OCRAExtended10", Fonts::OCRAExtended10);
    makeFont("OCRAExtended", "OCRAExtended11", Fonts::OCRAExtended11);
    makeFont("OCRAExtended", "OCRAExtended12", Fonts::OCRAExtended12);
    makeFont("OCRAExtended", "OCRAExtended13", Fonts::OCRAExtended13);
    makeFont("OCRAExtended", "OCRAExtended14", Fonts::OCRAExtended14);
    makeFont("OCRAExtended", "OCRAExtended15", Fonts::OCRAExtended15);
    makeFont("OCRAExtended", "OCRAExtended16", Fonts::OCRAExtended16);
    makeFont("OCRAExtended", "OCRAExtended17", Fonts::OCRAExtended17);
    makeFont("OCRAExtended", "OCRAExtended18", Fonts::OCRAExtended18);
    makeFont("OCRAExtended", "OCRAExtended19", Fonts::OCRAExtended19);
    makeFont("OCRAExtended", "OCRAExtended20", Fonts::OCRAExtended20);
    makeFont("OCRAExtended", "OCRAExtended21", Fonts::OCRAExtended21);
    makeFont("OCRAExtended", "OCRAExtended22", Fonts::OCRAExtended22);
    makeFont("OCRAExtended", "OCRAExtended23", Fonts::OCRAExtended23);
    makeFont("OCRAExtended", "OCRAExtended24", Fonts::OCRAExtended24);
    makeFont("OCRAExtended", "OCRAExtended25", Fonts::OCRAExtended25);
    makeFont("OCRAExtended", "OCRAExtended26", Fonts::OCRAExtended26);
    makeFont("OCRAExtended", "OCRAExtended27", Fonts::OCRAExtended27);
    makeFont("OCRAExtended", "OCRAExtended28", Fonts::OCRAExtended28);
    makeFont("OCRAExtended", "OCRAExtended29", Fonts::OCRAExtended29);
    makeFont("OCRAExtended", "OCRAExtended30", Fonts::OCRAExtended30);
    makeFont("OCRAExtended", "OCRAExtended31", Fonts::OCRAExtended31);
    makeFont("OCRAExtended", "OCRAExtended32", Fonts::OCRAExtended32);
    makeFont("OCRAExtended", "OCRAExtended33", Fonts::OCRAExtended33);
    makeFont("OCRAExtended", "OCRAExtended34", Fonts::OCRAExtended34);
    makeFont("OCRAExtended", "OCRAExtended35", Fonts::OCRAExtended35);
    makeFont("OCRAExtended", "OCRAExtended36", Fonts::OCRAExtended36);
    makeFont("OCRAExtended", "OCRAExtended37", Fonts::OCRAExtended37);
    makeFont("OCRAExtended", "OCRAExtended38", Fonts::OCRAExtended38);
    makeFont("OCRAExtended", "OCRAExtended39", Fonts::OCRAExtended39);
    makeFont("OCRAExtended", "OCRAExtended40", Fonts::OCRAExtended40);
    makeFont("OldStandard", "OldStandard10", Fonts::OldStandard10);
    makeFont("OldStandard", "OldStandard12", Fonts::OldStandard12);
    makeFont("OldStandard", "OldStandard14", Fonts::OldStandard14);
    makeFont("OldStandard", "OldStandard16", Fonts::OldStandard16);
    makeFont("OldStandard", "OldStandard18", Fonts::OldStandard18);
    makeFont("OldStandard", "OldStandard20", Fonts::OldStandard20);
    makeFont("OldStandard", "OldStandard22", Fonts::OldStandard22);
    makeFont("OldStandard", "OldStandard24", Fonts::OldStandard24);
    makeFont("OldStandard", "OldStandard26", Fonts::OldStandard26);
    makeFont("OldStandard", "OldStandard28", Fonts::OldStandard28);
    makeFont("OldStandard", "OldStandard30", Fonts::OldStandard30);
    makeFont("OldStandard", "OldStandard32", Fonts::OldStandard32);
    makeFont("OldStandard", "OldStandard34", Fonts::OldStandard34);
    makeFont("OldStandard", "OldStandard36", Fonts::OldStandard36);
    makeFont("OldStandard", "OldStandard38", Fonts::OldStandard38);
    makeFont("OldStandard", "OldStandard40", Fonts::OldStandard40);
    makeFont("OldStandard", "OldStandard8", Fonts::OldStandard8);
    makeFont("Open24Display", "Open24Display8", Fonts::Open24Display8);
    makeFont("Open24Display", "Open24Display10", Fonts::Open24Display10);
    makeFont("Open24Display", "Open24Display12", Fonts::Open24Display12);
    makeFont("Open24Display", "Open24Display14", Fonts::Open24Display14);
    makeFont("Open24Display", "Open24Display16", Fonts::Open24Display16);
    makeFont("Open24Display", "Open24Display18", Fonts::Open24Display18);
    makeFont("Open24Display", "Open24Display20", Fonts::Open24Display20);
    makeFont("Open24Display", "Open24Display22", Fonts::Open24Display22);
    makeFont("Open24Display", "Open24Display24", Fonts::Open24Display24);
    makeFont("Open24Display", "Open24Display26", Fonts::Open24Display26);
    makeFont("Open24Display", "Open24Display28", Fonts::Open24Display28);
    makeFont("Open24Display", "Open24Display30", Fonts::Open24Display30);
    makeFont("Open24Display", "Open24Display32", Fonts::Open24Display32);
    makeFont("Open24Display", "Open24Display34", Fonts::Open24Display34);
    makeFont("Open24Display", "Open24Display36", Fonts::Open24Display36);
    makeFont("Open24Display", "Open24Display38", Fonts::Open24Display38);
    makeFont("Open24Display", "Open24Display40", Fonts::Open24Display40);
    makeFont("PEARL8x8", "PEARL8x8", Fonts::PEARL8x8);
    makeFont("ProFont6x11", "ProFont6x11", Fonts::ProFont6x11);
    makeFont("RawGold", "RawGold", Fonts::RawGold);
    makeFont("Roboto", "Roboto", Fonts::Roboto);
    makeFont("SheepSans", "SheepSans8", Fonts::SheepSans8);
    makeFont("SheepSans", "SheepSans9", Fonts::SheepSans9);
    makeFont("SheepSans", "SheepSans10", Fonts::SheepSans10);
    makeFont("SheepSans", "SheepSans11", Fonts::SheepSans11);
    makeFont("SheepSans", "SheepSans12", Fonts::SheepSans12);
    makeFont("SheepSans", "SheepSans13", Fonts::SheepSans13);
    makeFont("SheepSans", "SheepSans14", Fonts::SheepSans14);
    makeFont("SheepSans", "SheepSans15", Fonts::SheepSans15);
    makeFont("SheepSans", "SheepSans16", Fonts::SheepSans16);
    makeFont("SheepSans", "SheepSans17", Fonts::SheepSans17);
    makeFont("SheepSans", "SheepSans18", Fonts::SheepSans18);
    makeFont("SheepSans", "SheepSans19", Fonts::SheepSans19);
    makeFont("SheepSans", "SheepSans20", Fonts::SheepSans20);
    makeFont("SheepSans", "SheepSans21", Fonts::SheepSans21);
    makeFont("SheepSans", "SheepSans22", Fonts::SheepSans22);
    makeFont("SheepSans", "SheepSans23", Fonts::SheepSans23);
    makeFont("SheepSans", "SheepSans24", Fonts::SheepSans24);
    makeFont("SheepSans", "SheepSans25", Fonts::SheepSans25);
    makeFont("SheepSans", "SheepSans26", Fonts::SheepSans26);
    makeFont("SheepSans", "SheepSans27", Fonts::SheepSans27);
    makeFont("SheepSans", "SheepSans28", Fonts::SheepSans28);
    makeFont("SheepSans", "SheepSans29", Fonts::SheepSans29);
    makeFont("SheepSans", "SheepSans30", Fonts::SheepSans30);
    makeFont("SheepSans", "SheepSans31", Fonts::SheepSans31);
    makeFont("SheepSans", "SheepSans32", Fonts::SheepSans32);
    makeFont("SheepSans", "SheepSans33", Fonts::SheepSans33);
    makeFont("SheepSans", "SheepSans34", Fonts::SheepSans34);
    makeFont("SheepSans", "SheepSans35", Fonts::SheepSans35);
    makeFont("SheepSans", "SheepSans36", Fonts::SheepSans36);
    makeFont("SheepSans", "SheepSans37", Fonts::SheepSans37);
    makeFont("SheepSans", "SheepSans38", Fonts::SheepSans38);
    makeFont("SheepSans", "SheepSans39", Fonts::SheepSans39);
    makeFont("SheepSans", "SheepSans40", Fonts::SheepSans40);
    makeFont("Sinclair", "Sinclair", Fonts::Sinclair);
    makeFont("Squircle", "Squircle", Fonts::Squircle);
    makeFont("SUN12x22", "SUN12x22", Fonts::SUN12x22);
    makeFont("SUN8x16", "SUN8x16", Fonts::SUN8x16);
    makeFont("Terminus6x12", "Terminus6x12", Fonts::Terminus6x12);
    makeFont("Topaz", "Topaz", Fonts::Topaz);
    makeFont("Ubuntu", "Ubuntu10", Fonts::Ubuntu10);
    makeFont("Ubuntu", "Ubuntu12", Fonts::Ubuntu12);
    makeFont("Ubuntu", "Ubuntu14", Fonts::Ubuntu14);
    makeFont("Ubuntu", "Ubuntu16", Fonts::Ubuntu16);
    makeFont("Ubuntu", "Ubuntu18", Fonts::Ubuntu18);
    makeFont("Ubuntu", "Ubuntu20", Fonts::Ubuntu20);
    makeFont("Ubuntu", "Ubuntu22", Fonts::Ubuntu22);
    makeFont("Ubuntu", "Ubuntu24", Fonts::Ubuntu24);
    makeFont("Ubuntu", "Ubuntu26", Fonts::Ubuntu26);
    makeFont("Ubuntu", "Ubuntu28", Fonts::Ubuntu28);
    makeFont("Ubuntu", "Ubuntu30", Fonts::Ubuntu30);
    makeFont("Ubuntu", "Ubuntu32", Fonts::Ubuntu32);
    makeFont("Ubuntu", "Ubuntu34", Fonts::Ubuntu34);
    makeFont("Ubuntu", "Ubuntu36", Fonts::Ubuntu36);
    makeFont("Ubuntu", "Ubuntu38", Fonts::Ubuntu38);
    makeFont("Ubuntu", "Ubuntu40", Fonts::Ubuntu40);
    makeFont("Ubuntu", "Ubuntu42", Fonts::Ubuntu42);
    makeFont("Ubuntu", "Ubuntu44", Fonts::Ubuntu44);
    makeFont("Ubuntu", "Ubuntu8", Fonts::Ubuntu8);
    makeFont("Unicode", "Unicode00", Fonts::Unicode00);
    makeFont("Unicode", "Unicode01", Fonts::Unicode01);
    makeFont("Unicode", "Unicode02", Fonts::Unicode02);
    makeFont("Unicode", "Unicode03", Fonts::Unicode03);
    makeFont("Unicode", "Unicode04", Fonts::Unicode04);
    makeFont("Unicode", "Unicode05", Fonts::Unicode05);
    makeFont("Unicode", "Unicode06", Fonts::Unicode06);
    makeFont("Unicode", "Unicode07", Fonts::Unicode07);
    makeFont("Unicode", "Unicode08", Fonts::Unicode08);
    makeFont("Unicode", "Unicode09", Fonts::Unicode09);
    makeFont("Unicode", "Unicode0A", Fonts::Unicode0A);
    makeFont("Unicode", "Unicode0B", Fonts::Unicode0B);
    makeFont("Unicode", "Unicode0C", Fonts::Unicode0C);
    makeFont("Unicode", "Unicode0D", Fonts::Unicode0D);
    makeFont("Unicode", "Unicode0E", Fonts::Unicode0E);
    makeFont("Unicode", "Unicode0F", Fonts::Unicode0F);
    makeFont("Unicode", "Unicode10", Fonts::Unicode10);
    makeFont("Unicode", "Unicode11", Fonts::Unicode11);
    makeFont("Unicode", "Unicode12", Fonts::Unicode12);
    makeFont("Unicode", "Unicode13", Fonts::Unicode13);
    makeFont("Unicode", "Unicode14", Fonts::Unicode14);
    makeFont("Unicode", "Unicode15", Fonts::Unicode15);
    makeFont("Unicode", "Unicode16", Fonts::Unicode16);
    makeFont("Unicode", "Unicode17", Fonts::Unicode17);
    makeFont("Unicode", "Unicode18", Fonts::Unicode18);
    makeFont("Unicode", "Unicode19", Fonts::Unicode19);
    makeFont("Unicode", "Unicode1A", Fonts::Unicode1A);
    makeFont("Unicode", "Unicode1B", Fonts::Unicode1B);
    makeFont("Unicode", "Unicode1C", Fonts::Unicode1C);
    makeFont("Unicode", "Unicode1D", Fonts::Unicode1D);
    makeFont("Unicode", "Unicode1E", Fonts::Unicode1E);
    makeFont("Unicode", "Unicode1F", Fonts::Unicode1F);
    makeFont("Unicode", "Unicode20", Fonts::Unicode20);
    makeFont("Unicode", "Unicode21", Fonts::Unicode21);
    makeFont("Unicode", "Unicode22", Fonts::Unicode22);
    makeFont("Unicode", "Unicode23", Fonts::Unicode23);
    makeFont("Unicode", "Unicode24", Fonts::Unicode24);
    makeFont("Unicode", "Unicode25", Fonts::Unicode25);
    makeFont("Unicode", "Unicode26", Fonts::Unicode26);
    makeFont("Unicode", "Unicode27", Fonts::Unicode27);
    makeFont("Unicode", "Unicode28", Fonts::Unicode28);
    makeFont("Unicode", "Unicode29", Fonts::Unicode29);
    makeFont("Unicode", "Unicode2A", Fonts::Unicode2A);
    makeFont("Unicode", "Unicode2B", Fonts::Unicode2B);
    makeFont("Unicode", "Unicode2C", Fonts::Unicode2C);
    makeFont("Unicode", "Unicode2D", Fonts::Unicode2D);
    makeFont("Unicode", "Unicode2E", Fonts::Unicode2E);
    makeFont("Unicode", "Unicode2F", Fonts::Unicode2F);
    makeFont("Unicode", "Unicode30", Fonts::Unicode30);
    makeFont("Unicode", "Unicode31", Fonts::Unicode31);
    makeFont("Unicode", "Unicode32", Fonts::Unicode32);
    makeFont("Unicode", "Unicode33", Fonts::Unicode33);
    makeFont("Unicode", "Unicode34", Fonts::Unicode34);
    makeFont("Unicode", "Unicode35", Fonts::Unicode35);
    makeFont("Unicode", "Unicode36", Fonts::Unicode36);
    makeFont("Unicode", "Unicode37", Fonts::Unicode37);
    makeFont("Unicode", "Unicode38", Fonts::Unicode38);
    makeFont("Unicode", "Unicode39", Fonts::Unicode39);
    makeFont("Unicode", "Unicode3A", Fonts::Unicode3A);
    makeFont("Unicode", "Unicode3B", Fonts::Unicode3B);
    makeFont("Unicode", "Unicode3C", Fonts::Unicode3C);
    makeFont("Unicode", "Unicode3D", Fonts::Unicode3D);
    makeFont("Unicode", "Unicode3E", Fonts::Unicode3E);
    makeFont("Unicode", "Unicode3F", Fonts::Unicode3F);
    makeFont("Unicode", "Unicode40", Fonts::Unicode40);
    makeFont("Unicode", "Unicode41", Fonts::Unicode41);
    makeFont("Unicode", "Unicode42", Fonts::Unicode42);
    makeFont("Unicode", "Unicode43", Fonts::Unicode43);
    makeFont("Unicode", "Unicode44", Fonts::Unicode44);
    makeFont("Unicode", "Unicode45", Fonts::Unicode45);
    makeFont("Unicode", "Unicode46", Fonts::Unicode46);
    makeFont("Unicode", "Unicode47", Fonts::Unicode47);
    makeFont("Unicode", "Unicode48", Fonts::Unicode48);
    makeFont("Unicode", "Unicode49", Fonts::Unicode49);
    makeFont("Unicode", "Unicode4A", Fonts::Unicode4A);
    makeFont("Unicode", "Unicode4B", Fonts::Unicode4B);
    makeFont("Unicode", "Unicode4C", Fonts::Unicode4C);
    makeFont("Unicode", "Unicode4D", Fonts::Unicode4D);
    makeFont("Unicode", "Unicode4E", Fonts::Unicode4E);
    makeFont("Unicode", "Unicode4F", Fonts::Unicode4F);
    makeFont("Unicode", "Unicode50", Fonts::Unicode50);
    makeFont("Unicode", "Unicode51", Fonts::Unicode51);
    makeFont("Unicode", "Unicode52", Fonts::Unicode52);
    makeFont("Unicode", "Unicode53", Fonts::Unicode53);
    makeFont("Unicode", "Unicode54", Fonts::Unicode54);
    makeFont("Unicode", "Unicode55", Fonts::Unicode55);
    makeFont("Unicode", "Unicode56", Fonts::Unicode56);
    makeFont("Unicode", "Unicode57", Fonts::Unicode57);
    makeFont("Unicode", "Unicode58", Fonts::Unicode58);
    makeFont("Unicode", "Unicode59", Fonts::Unicode59);
    makeFont("Unicode", "Unicode5A", Fonts::Unicode5A);
    makeFont("Unicode", "Unicode5B", Fonts::Unicode5B);
    makeFont("Unicode", "Unicode5C", Fonts::Unicode5C);
    makeFont("Unicode", "Unicode5D", Fonts::Unicode5D);
    makeFont("Unicode", "Unicode5E", Fonts::Unicode5E);
    makeFont("Unicode", "Unicode5F", Fonts::Unicode5F);
    makeFont("Unicode", "Unicode60", Fonts::Unicode60);
    makeFont("Unicode", "Unicode61", Fonts::Unicode61);
    makeFont("Unicode", "Unicode62", Fonts::Unicode62);
    makeFont("Unicode", "Unicode63", Fonts::Unicode63);
    makeFont("Unicode", "Unicode64", Fonts::Unicode64);
    makeFont("Unicode", "Unicode65", Fonts::Unicode65);
    makeFont("Unicode", "Unicode66", Fonts::Unicode66);
    makeFont("Unicode", "Unicode67", Fonts::Unicode67);
    makeFont("Unicode", "Unicode68", Fonts::Unicode68);
    makeFont("Unicode", "Unicode69", Fonts::Unicode69);
    makeFont("Unicode", "Unicode6A", Fonts::Unicode6A);
    makeFont("Unicode", "Unicode6B", Fonts::Unicode6B);
    makeFont("Unicode", "Unicode6C", Fonts::Unicode6C);
    makeFont("Unicode", "Unicode6D", Fonts::Unicode6D);
    makeFont("Unicode", "Unicode6E", Fonts::Unicode6E);
    makeFont("Unicode", "Unicode6F", Fonts::Unicode6F);
    makeFont("Unicode", "Unicode70", Fonts::Unicode70);
    makeFont("Unicode", "Unicode71", Fonts::Unicode71);
    makeFont("Unicode", "Unicode72", Fonts::Unicode72);
    makeFont("Unicode", "Unicode73", Fonts::Unicode73);
    makeFont("Unicode", "Unicode74", Fonts::Unicode74);
    makeFont("Unicode", "Unicode75", Fonts::Unicode75);
    makeFont("Unicode", "Unicode76", Fonts::Unicode76);
    makeFont("Unicode", "Unicode77", Fonts::Unicode77);
    makeFont("Unicode", "Unicode78", Fonts::Unicode78);
    makeFont("Unicode", "Unicode79", Fonts::Unicode79);
    makeFont("Unicode", "Unicode7A", Fonts::Unicode7A);
    makeFont("Unicode", "Unicode7B", Fonts::Unicode7B);
    makeFont("Unicode", "Unicode7C", Fonts::Unicode7C);
    makeFont("Unicode", "Unicode7D", Fonts::Unicode7D);
    makeFont("Unicode", "Unicode7E", Fonts::Unicode7E);
    makeFont("Unicode", "Unicode7F", Fonts::Unicode7F);
    makeFont("Unicode", "Unicode80", Fonts::Unicode80);
    makeFont("Unicode", "Unicode81", Fonts::Unicode81);
    makeFont("Unicode", "Unicode82", Fonts::Unicode82);
    makeFont("Unicode", "Unicode83", Fonts::Unicode83);
    makeFont("Unicode", "Unicode84", Fonts::Unicode84);
    makeFont("Unicode", "Unicode85", Fonts::Unicode85);
    makeFont("Unicode", "Unicode86", Fonts::Unicode86);
    makeFont("Unicode", "Unicode87", Fonts::Unicode87);
    makeFont("Unicode", "Unicode88", Fonts::Unicode88);
    makeFont("Unicode", "Unicode89", Fonts::Unicode89);
    makeFont("Unicode", "Unicode8A", Fonts::Unicode8A);
    makeFont("Unicode", "Unicode8B", Fonts::Unicode8B);
    makeFont("Unicode", "Unicode8C", Fonts::Unicode8C);
    makeFont("Unicode", "Unicode8D", Fonts::Unicode8D);
    makeFont("Unicode", "Unicode8E", Fonts::Unicode8E);
    makeFont("Unicode", "Unicode8F", Fonts::Unicode8F);
    makeFont("Unicode", "Unicode90", Fonts::Unicode90);
    makeFont("Unicode", "Unicode91", Fonts::Unicode91);
    makeFont("Unicode", "Unicode92", Fonts::Unicode92);
    makeFont("Unicode", "Unicode93", Fonts::Unicode93);
    makeFont("Unicode", "Unicode94", Fonts::Unicode94);
    makeFont("Unicode", "Unicode95", Fonts::Unicode95);
    makeFont("Unicode", "Unicode96", Fonts::Unicode96);
    makeFont("Unicode", "Unicode97", Fonts::Unicode97);
    makeFont("Unicode", "Unicode98", Fonts::Unicode98);
    makeFont("Unicode", "Unicode99", Fonts::Unicode99);
    makeFont("Unicode", "Unicode9A", Fonts::Unicode9A);
    makeFont("Unicode", "Unicode9B", Fonts::Unicode9B);
    makeFont("Unicode", "Unicode9C", Fonts::Unicode9C);
    makeFont("Unicode", "Unicode9D", Fonts::Unicode9D);
    makeFont("Unicode", "Unicode9E", Fonts::Unicode9E);
    makeFont("Unicode", "Unicode9F", Fonts::Unicode9F);
    makeFont("Unicode", "UnicodeA0", Fonts::UnicodeA0);
    makeFont("Unicode", "UnicodeA1", Fonts::UnicodeA1);
    makeFont("Unicode", "UnicodeA2", Fonts::UnicodeA2);
    makeFont("Unicode", "UnicodeA3", Fonts::UnicodeA3);
    makeFont("Unicode", "UnicodeA4", Fonts::UnicodeA4);
    makeFont("Unicode", "UnicodeA5", Fonts::UnicodeA5);
    makeFont("Unicode", "UnicodeA6", Fonts::UnicodeA6);
    makeFont("Unicode", "UnicodeA7", Fonts::UnicodeA7);
    makeFont("Unicode", "UnicodeA8", Fonts::UnicodeA8);
    makeFont("Unicode", "UnicodeA9", Fonts::UnicodeA9);
    makeFont("Unicode", "UnicodeAA", Fonts::UnicodeAA);
    makeFont("Unicode", "UnicodeAB", Fonts::UnicodeAB);
    makeFont("Unicode", "UnicodeAC", Fonts::UnicodeAC);
    makeFont("Unicode", "UnicodeAD", Fonts::UnicodeAD);
    makeFont("Unicode", "UnicodeAE", Fonts::UnicodeAE);
    makeFont("Unicode", "UnicodeAF", Fonts::UnicodeAF);
    makeFont("Unicode", "UnicodeB0", Fonts::UnicodeB0);
    makeFont("Unicode", "UnicodeB1", Fonts::UnicodeB1);
    makeFont("Unicode", "UnicodeB2", Fonts::UnicodeB2);
    makeFont("Unicode", "UnicodeB3", Fonts::UnicodeB3);
    makeFont("Unicode", "UnicodeB4", Fonts::UnicodeB4);
    makeFont("Unicode", "UnicodeB5", Fonts::UnicodeB5);
    makeFont("Unicode", "UnicodeB6", Fonts::UnicodeB6);
    makeFont("Unicode", "UnicodeB7", Fonts::UnicodeB7);
    makeFont("Unicode", "UnicodeB8", Fonts::UnicodeB8);
    makeFont("Unicode", "UnicodeB9", Fonts::UnicodeB9);
    makeFont("Unicode", "UnicodeBA", Fonts::UnicodeBA);
    makeFont("Unicode", "UnicodeBB", Fonts::UnicodeBB);
    makeFont("Unicode", "UnicodeBC", Fonts::UnicodeBC);
    makeFont("Unicode", "UnicodeBD", Fonts::UnicodeBD);
    makeFont("Unicode", "UnicodeBE", Fonts::UnicodeBE);
    makeFont("Unicode", "UnicodeBF", Fonts::UnicodeBF);
    makeFont("Unicode", "UnicodeC0", Fonts::UnicodeC0);
    makeFont("Unicode", "UnicodeC1", Fonts::UnicodeC1);
    makeFont("Unicode", "UnicodeC2", Fonts::UnicodeC2);
    makeFont("Unicode", "UnicodeC3", Fonts::UnicodeC3);
    makeFont("Unicode", "UnicodeC4", Fonts::UnicodeC4);
    makeFont("Unicode", "UnicodeC5", Fonts::UnicodeC5);
    makeFont("Unicode", "UnicodeC6", Fonts::UnicodeC6);
    makeFont("Unicode", "UnicodeC7", Fonts::UnicodeC7);
    makeFont("Unicode", "UnicodeC8", Fonts::UnicodeC8);
    makeFont("Unicode", "UnicodeC9", Fonts::UnicodeC9);
    makeFont("Unicode", "UnicodeCA", Fonts::UnicodeCA);
    makeFont("Unicode", "UnicodeCB", Fonts::UnicodeCB);
    makeFont("Unicode", "UnicodeCC", Fonts::UnicodeCC);
    makeFont("Unicode", "UnicodeCD", Fonts::UnicodeCD);
    makeFont("Unicode", "UnicodeCE", Fonts::UnicodeCE);
    makeFont("Unicode", "UnicodeCF", Fonts::UnicodeCF);
    makeFont("Unicode", "UnicodeD0", Fonts::UnicodeD0);
    makeFont("Unicode", "UnicodeD1", Fonts::UnicodeD1);
    makeFont("Unicode", "UnicodeD2", Fonts::UnicodeD2);
    makeFont("Unicode", "UnicodeD3", Fonts::UnicodeD3);
    makeFont("Unicode", "UnicodeD4", Fonts::UnicodeD4);
    makeFont("Unicode", "UnicodeD5", Fonts::UnicodeD5);
    makeFont("Unicode", "UnicodeD6", Fonts::UnicodeD6);
    makeFont("Unicode", "UnicodeD7", Fonts::UnicodeD7);
    makeFont("Unicode", "UnicodeD8", Fonts::UnicodeD8);
    makeFont("Unicode", "UnicodeD9", Fonts::UnicodeD9);
    makeFont("Unicode", "UnicodeDA", Fonts::UnicodeDA);
    makeFont("Unicode", "UnicodeDB", Fonts::UnicodeDB);
    makeFont("Unicode", "UnicodeDC", Fonts::UnicodeDC);
    makeFont("Unicode", "UnicodeDD", Fonts::UnicodeDD);
    makeFont("Unicode", "UnicodeDE", Fonts::UnicodeDE);
    makeFont("Unicode", "UnicodeDF", Fonts::UnicodeDF);
    makeFont("Unicode", "UnicodeE0", Fonts::UnicodeE0);
    makeFont("Unicode", "UnicodeE1", Fonts::UnicodeE1);
    makeFont("Unicode", "UnicodeE2", Fonts::UnicodeE2);
    makeFont("Unicode", "UnicodeE3", Fonts::UnicodeE3);
    makeFont("Unicode", "UnicodeE4", Fonts::UnicodeE4);
    makeFont("Unicode", "UnicodeE5", Fonts::UnicodeE5);
    makeFont("Unicode", "UnicodeE6", Fonts::UnicodeE6);
    makeFont("Unicode", "UnicodeE7", Fonts::UnicodeE7);
    makeFont("Unicode", "UnicodeE8", Fonts::UnicodeE8);
    makeFont("Unicode", "UnicodeE9", Fonts::UnicodeE9);
    makeFont("Unicode", "UnicodeEA", Fonts::UnicodeEA);
    makeFont("Unicode", "UnicodeEB", Fonts::UnicodeEB);
    makeFont("Unicode", "UnicodeEC", Fonts::UnicodeEC);
    makeFont("Unicode", "UnicodeED", Fonts::UnicodeED);
    makeFont("Unicode", "UnicodeEE", Fonts::UnicodeEE);
    makeFont("Unicode", "UnicodeEF", Fonts::UnicodeEF);
    makeFont("Unicode", "UnicodeF0", Fonts::UnicodeF0);
    makeFont("Unicode", "UnicodeF1", Fonts::UnicodeF1);
    makeFont("Unicode", "UnicodeF2", Fonts::UnicodeF2);
    makeFont("Unicode", "UnicodeF3", Fonts::UnicodeF3);
    makeFont("Unicode", "UnicodeF4", Fonts::UnicodeF4);
    makeFont("Unicode", "UnicodeF5", Fonts::UnicodeF5);
    makeFont("Unicode", "UnicodeF6", Fonts::UnicodeF6);
    makeFont("Unicode", "UnicodeF7", Fonts::UnicodeF7);
    makeFont("Unicode", "UnicodeF8", Fonts::UnicodeF8);
    makeFont("Unicode", "UnicodeF9", Fonts::UnicodeF9);
    makeFont("Unicode", "UnicodeFA", Fonts::UnicodeFA);
    makeFont("Unicode", "UnicodeFB", Fonts::UnicodeFB);
    makeFont("Unicode", "UnicodeFC", Fonts::UnicodeFC);
    makeFont("Unicode", "UnicodeFD", Fonts::UnicodeFD);
    makeFont("Unicode", "UnicodeFE", Fonts::UnicodeFE);
    makeFont("Unicode", "UnicodeFF", Fonts::UnicodeFF);
    makeFont("VGA8x16", "VGA8x16", Fonts::VGA8x16);
    makeFont("VGA8x8", "VGA8x8", Fonts::VGA8x8);
    makeFont("XTerm", "XTerm", Fonts::XTerm);
    makeFont("Clive", "Clive", Fonts::Clive);
    makeFont("Pipes", "Pipes", Fonts::Pipes);
}
