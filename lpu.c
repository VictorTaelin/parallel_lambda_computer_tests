#include <stdio.h>

// Uncomment the line with the desired difficulty you want to benchamrk.
//const int difficulty = 1; const int memory_nodes = 20; const int clocks = 19; const int program[] = {3,2,3,-1,0,0,0,0,3,4,5,-2,0,0,0,0,3,-4,6,7,0,0,0,0,3,-6,8,9,0,0,0,0,3,-7,-8,-9,0,0,0,0,3,-5,10,11,0,0,0,0,3,-10,12,13,0,0,0,0,3,-11,-12,-13,0,0,0,0,3,-3,14,-14};
//const int difficulty = 2; const int memory_nodes = 40; const int clocks = 61; const int program[] = {3,2,3,-1,0,0,0,0,3,4,5,-2,0,0,0,0,3,-4,6,7,0,0,0,0,4,-6,8,9,0,0,0,0,3,-8,10,11,0,0,0,0,3,-7,-10,12,0,0,0,0,3,-9,-11,-12,0,0,0,0,3,-5,13,14,0,0,0,0,5,-13,15,16,0,0,0,0,3,-15,17,18,0,0,0,0,3,-14,-17,19,0,0,0,0,3,-16,-18,-19,0,0,0,0,3,-3,20,-20};
//const int difficulty = 3; const int memory_nodes = 60; const int clocks = 105; const int program[] = {3,2,3,-1,0,0,0,0,3,4,5,-2,0,0,0,0,3,-4,6,7,0,0,0,0,5,-6,8,9,0,0,0,0,3,-8,10,11,0,0,0,0,3,-7,-10,12,0,0,0,0,3,13,14,-12,0,0,0,0,4,-9,15,-13,0,0,0,0,3,-15,-11,-14,0,0,0,0,3,-5,16,17,0,0,0,0,7,-16,18,19,0,0,0,0,3,-18,20,21,0,0,0,0,3,-17,-20,22,0,0,0,0,3,23,24,-22,0,0,0,0,6,-19,25,-23,0,0,0,0,3,-25,-21,-24,0,0,0,0,3,-3,26,-26};
//const int difficulty = 4; const int memory_nodes = 80; const int clocks = 182; const int program[] = {3,2,3,-1,0,0,0,0,3,4,5,-2,0,0,0,0,3,-4,6,7,0,0,0,0,6,-6,8,9,0,0,0,0,3,-8,10,11,0,0,0,0,3,-7,-10,12,0,0,0,0,3,13,14,-12,0,0,0,0,4,15,16,-13,0,0,0,0,5,-9,17,-15,0,0,0,0,3,-17,-11,18,0,0,0,0,3,-16,-18,-14,0,0,0,0,3,-5,19,20,0,0,0,0,9,-19,21,22,0,0,0,0,3,-21,23,24,0,0,0,0,3,-20,-23,25,0,0,0,0,3,26,27,-25,0,0,0,0,7,28,29,-26,0,0,0,0,8,-22,30,-28,0,0,0,0,3,-30,-24,31,0,0,0,0,3,-29,-31,-27,0,0,0,0,3,-3,32,-32};
//const int difficulty = 5; const int memory_nodes = 110; const int clocks = 280; const int program[] = {3,2,3,-1,0,0,0,0,3,4,5,-2,0,0,0,0,3,-4,6,7,0,0,0,0,7,-6,8,9,0,0,0,0,3,-8,10,11,0,0,0,0,3,-7,-10,12,0,0,0,0,3,13,14,-12,0,0,0,0,4,15,16,-13,0,0,0,0,5,17,18,-15,0,0,0,0,6,-9,19,-17,0,0,0,0,3,-19,-11,20,0,0,0,0,3,-18,-20,21,0,0,0,0,3,-16,-21,-14,0,0,0,0,3,-5,22,23,0,0,0,0,11,-22,24,25,0,0,0,0,3,-24,26,27,0,0,0,0,3,-23,-26,28,0,0,0,0,3,29,30,-28,0,0,0,0,8,31,32,-29,0,0,0,0,9,33,34,-31,0,0,0,0,10,-25,35,-33,0,0,0,0,3,-35,-27,36,0,0,0,0,3,-34,-36,37,0,0,0,0,3,-32,-37,-30,0,0,0,0,3,-3,38,-38};
//const int difficulty = 10; const int memory_nodes = 800; const int clocks = 2600; const int program[] = {3,2,3,-1,0,0,0,0,3,4,5,-2,0,0,0,0,3,-4,6,7,0,0,0,0,12,-6,8,9,0,0,0,0,3,-8,10,11,0,0,0,0,3,-7,-10,12,0,0,0,0,3,13,14,-12,0,0,0,0,4,15,16,-13,0,0,0,0,5,17,18,-15,0,0,0,0,6,19,20,-17,0,0,0,0,7,21,22,-19,0,0,0,0,8,23,24,-21,0,0,0,0,9,25,26,-23,0,0,0,0,10,27,28,-25,0,0,0,0,11,-9,29,-27,0,0,0,0,3,-29,-11,30,0,0,0,0,3,-28,-30,31,0,0,0,0,3,-26,-31,32,0,0,0,0,3,-24,-32,33,0,0,0,0,3,-22,-33,34,0,0,0,0,3,-20,-34,35,0,0,0,0,3,-18,-35,36,0,0,0,0,3,-16,-36,-14,0,0,0,0,3,-5,37,38,0,0,0,0,21,-37,39,40,0,0,0,0,3,-39,41,42,0,0,0,0,3,-38,-41,43,0,0,0,0,3,44,45,-43,0,0,0,0,13,46,47,-44,0,0,0,0,14,48,49,-46,0,0,0,0,15,50,51,-48,0,0,0,0,16,52,53,-50,0,0,0,0,17,54,55,-52,0,0,0,0,18,56,57,-54,0,0,0,0,19,58,59,-56,0,0,0,0,20,-40,60,-58,0,0,0,0,3,-60,-42,61,0,0,0,0,3,-59,-61,62,0,0,0,0,3,-57,-62,63,0,0,0,0,3,-55,-63,64,0,0,0,0,3,-53,-64,65,0,0,0,0,3,-51,-65,66,0,0,0,0,3,-49,-66,67,0,0,0,0,3,-47,-67,-45,0,0,0,0,3,-3,68,-68};
//const int difficulty = 20; const int memory_nodes = 1000; const int clocks = 4400; const int program[] = {3,2,3,-1,0,0,0,0,3,4,5,-2,0,0,0,0,3,-4,6,7,0,0,0,0,22,-6,8,9,0,0,0,0,3,-8,10,11,0,0,0,0,3,-7,-10,12,0,0,0,0,3,13,14,-12,0,0,0,0,4,15,16,-13,0,0,0,0,5,17,18,-15,0,0,0,0,6,19,20,-17,0,0,0,0,7,21,22,-19,0,0,0,0,8,23,24,-21,0,0,0,0,9,25,26,-23,0,0,0,0,10,27,28,-25,0,0,0,0,11,29,30,-27,0,0,0,0,12,31,32,-29,0,0,0,0,13,33,34,-31,0,0,0,0,14,35,36,-33,0,0,0,0,15,37,38,-35,0,0,0,0,16,39,40,-37,0,0,0,0,17,41,42,-39,0,0,0,0,18,43,44,-41,0,0,0,0,19,45,46,-43,0,0,0,0,20,47,48,-45,0,0,0,0,21,-9,49,-47,0,0,0,0,3,-49,-11,50,0,0,0,0,3,-48,-50,51,0,0,0,0,3,-46,-51,52,0,0,0,0,3,-44,-52,53,0,0,0,0,3,-42,-53,54,0,0,0,0,3,-40,-54,55,0,0,0,0,3,-38,-55,56,0,0,0,0,3,-36,-56,57,0,0,0,0,3,-34,-57,58,0,0,0,0,3,-32,-58,59,0,0,0,0,3,-30,-59,60,0,0,0,0,3,-28,-60,61,0,0,0,0,3,-26,-61,62,0,0,0,0,3,-24,-62,63,0,0,0,0,3,-22,-63,64,0,0,0,0,3,-20,-64,65,0,0,0,0,3,-18,-65,66,0,0,0,0,3,-16,-66,-14,0,0,0,0,3,-5,67,68,0,0,0,0,41,-67,69,70,0,0,0,0,3,-69,71,72,0,0,0,0,3,-68,-71,73,0,0,0,0,3,74,75,-73,0,0,0,0,23,76,77,-74,0,0,0,0,24,78,79,-76,0,0,0,0,25,80,81,-78,0,0,0,0,26,82,83,-80,0,0,0,0,27,84,85,-82,0,0,0,0,28,86,87,-84,0,0,0,0,29,88,89,-86,0,0,0,0,30,90,91,-88,0,0,0,0,31,92,93,-90,0,0,0,0,32,94,95,-92,0,0,0,0,33,96,97,-94,0,0,0,0,34,98,99,-96,0,0,0,0,35,100,101,-98,0,0,0,0,36,102,103,-100,0,0,0,0,37,104,105,-102,0,0,0,0,38,106,107,-104,0,0,0,0,39,108,109,-106,0,0,0,0,40,-70,110,-108,0,0,0,0,3,-110,-72,111,0,0,0,0,3,-109,-111,112,0,0,0,0,3,-107,-112,113,0,0,0,0,3,-105,-113,114,0,0,0,0,3,-103,-114,115,0,0,0,0,3,-101,-115,116,0,0,0,0,3,-99,-116,117,0,0,0,0,3,-97,-117,118,0,0,0,0,3,-95,-118,119,0,0,0,0,3,-93,-119,120,0,0,0,0,3,-91,-120,121,0,0,0,0,3,-89,-121,122,0,0,0,0,3,-87,-122,123,0,0,0,0,3,-85,-123,124,0,0,0,0,3,-83,-124,125,0,0,0,0,3,-81,-125,126,0,0,0,0,3,-79,-126,127,0,0,0,0,3,-77,-127,-75,0,0,0,0,3,-3,128,-128};
const int difficulty = 50; const int memory_nodes = 5000; const int clocks = 26000; const int program[] = {3,2,3,-1,0,0,0,0,3,4,5,-2,0,0,0,0,3,-4,6,7,0,0,0,0,52,-6,8,9,0,0,0,0,3,-8,10,11,0,0,0,0,3,-7,-10,12,0,0,0,0,3,13,14,-12,0,0,0,0,4,15,16,-13,0,0,0,0,5,17,18,-15,0,0,0,0,6,19,20,-17,0,0,0,0,7,21,22,-19,0,0,0,0,8,23,24,-21,0,0,0,0,9,25,26,-23,0,0,0,0,10,27,28,-25,0,0,0,0,11,29,30,-27,0,0,0,0,12,31,32,-29,0,0,0,0,13,33,34,-31,0,0,0,0,14,35,36,-33,0,0,0,0,15,37,38,-35,0,0,0,0,16,39,40,-37,0,0,0,0,17,41,42,-39,0,0,0,0,18,43,44,-41,0,0,0,0,19,45,46,-43,0,0,0,0,20,47,48,-45,0,0,0,0,21,49,50,-47,0,0,0,0,22,51,52,-49,0,0,0,0,23,53,54,-51,0,0,0,0,24,55,56,-53,0,0,0,0,25,57,58,-55,0,0,0,0,26,59,60,-57,0,0,0,0,27,61,62,-59,0,0,0,0,28,63,64,-61,0,0,0,0,29,65,66,-63,0,0,0,0,30,67,68,-65,0,0,0,0,31,69,70,-67,0,0,0,0,32,71,72,-69,0,0,0,0,33,73,74,-71,0,0,0,0,34,75,76,-73,0,0,0,0,35,77,78,-75,0,0,0,0,36,79,80,-77,0,0,0,0,37,81,82,-79,0,0,0,0,38,83,84,-81,0,0,0,0,39,85,86,-83,0,0,0,0,40,87,88,-85,0,0,0,0,41,89,90,-87,0,0,0,0,42,91,92,-89,0,0,0,0,43,93,94,-91,0,0,0,0,44,95,96,-93,0,0,0,0,45,97,98,-95,0,0,0,0,46,99,100,-97,0,0,0,0,47,101,102,-99,0,0,0,0,48,103,104,-101,0,0,0,0,49,105,106,-103,0,0,0,0,50,107,108,-105,0,0,0,0,51,-9,109,-107,0,0,0,0,3,-109,-11,110,0,0,0,0,3,-108,-110,111,0,0,0,0,3,-106,-111,112,0,0,0,0,3,-104,-112,113,0,0,0,0,3,-102,-113,114,0,0,0,0,3,-100,-114,115,0,0,0,0,3,-98,-115,116,0,0,0,0,3,-96,-116,117,0,0,0,0,3,-94,-117,118,0,0,0,0,3,-92,-118,119,0,0,0,0,3,-90,-119,120,0,0,0,0,3,-88,-120,121,0,0,0,0,3,-86,-121,122,0,0,0,0,3,-84,-122,123,0,0,0,0,3,-82,-123,124,0,0,0,0,3,-80,-124,125,0,0,0,0,3,-78,-125,126,0,0,0,0,3,-76,-126,127,0,0,0,0,3,-74,-127,128,0,0,0,0,3,-72,-128,129,0,0,0,0,3,-70,-129,130,0,0,0,0,3,-68,-130,131,0,0,0,0,3,-66,-131,132,0,0,0,0,3,-64,-132,133,0,0,0,0,3,-62,-133,134,0,0,0,0,3,-60,-134,135,0,0,0,0,3,-58,-135,136,0,0,0,0,3,-56,-136,137,0,0,0,0,3,-54,-137,138,0,0,0,0,3,-52,-138,139,0,0,0,0,3,-50,-139,140,0,0,0,0,3,-48,-140,141,0,0,0,0,3,-46,-141,142,0,0,0,0,3,-44,-142,143,0,0,0,0,3,-42,-143,144,0,0,0,0,3,-40,-144,145,0,0,0,0,3,-38,-145,146,0,0,0,0,3,-36,-146,147,0,0,0,0,3,-34,-147,148,0,0,0,0,3,-32,-148,149,0,0,0,0,3,-30,-149,150,0,0,0,0,3,-28,-150,151,0,0,0,0,3,-26,-151,152,0,0,0,0,3,-24,-152,153,0,0,0,0,3,-22,-153,154,0,0,0,0,3,-20,-154,155,0,0,0,0,3,-18,-155,156,0,0,0,0,3,-16,-156,-14,0,0,0,0,3,-5,157,158,0,0,0,0,101,-157,159,160,0,0,0,0,3,-159,161,162,0,0,0,0,3,-158,-161,163,0,0,0,0,3,164,165,-163,0,0,0,0,53,166,167,-164,0,0,0,0,54,168,169,-166,0,0,0,0,55,170,171,-168,0,0,0,0,56,172,173,-170,0,0,0,0,57,174,175,-172,0,0,0,0,58,176,177,-174,0,0,0,0,59,178,179,-176,0,0,0,0,60,180,181,-178,0,0,0,0,61,182,183,-180,0,0,0,0,62,184,185,-182,0,0,0,0,63,186,187,-184,0,0,0,0,64,188,189,-186,0,0,0,0,65,190,191,-188,0,0,0,0,66,192,193,-190,0,0,0,0,67,194,195,-192,0,0,0,0,68,196,197,-194,0,0,0,0,69,198,199,-196,0,0,0,0,70,200,201,-198,0,0,0,0,71,202,203,-200,0,0,0,0,72,204,205,-202,0,0,0,0,73,206,207,-204,0,0,0,0,74,208,209,-206,0,0,0,0,75,210,211,-208,0,0,0,0,76,212,213,-210,0,0,0,0,77,214,215,-212,0,0,0,0,78,216,217,-214,0,0,0,0,79,218,219,-216,0,0,0,0,80,220,221,-218,0,0,0,0,81,222,223,-220,0,0,0,0,82,224,225,-222,0,0,0,0,83,226,227,-224,0,0,0,0,84,228,229,-226,0,0,0,0,85,230,231,-228,0,0,0,0,86,232,233,-230,0,0,0,0,87,234,235,-232,0,0,0,0,88,236,237,-234,0,0,0,0,89,238,239,-236,0,0,0,0,90,240,241,-238,0,0,0,0,91,242,243,-240,0,0,0,0,92,244,245,-242,0,0,0,0,93,246,247,-244,0,0,0,0,94,248,249,-246,0,0,0,0,95,250,251,-248,0,0,0,0,96,252,253,-250,0,0,0,0,97,254,255,-252,0,0,0,0,98,256,257,-254,0,0,0,0,99,258,259,-256,0,0,0,0,100,-160,260,-258,0,0,0,0,3,-260,-162,261,0,0,0,0,3,-259,-261,262,0,0,0,0,3,-257,-262,263,0,0,0,0,3,-255,-263,264,0,0,0,0,3,-253,-264,265,0,0,0,0,3,-251,-265,266,0,0,0,0,3,-249,-266,267,0,0,0,0,3,-247,-267,268,0,0,0,0,3,-245,-268,269,0,0,0,0,3,-243,-269,270,0,0,0,0,3,-241,-270,271,0,0,0,0,3,-239,-271,272,0,0,0,0,3,-237,-272,273,0,0,0,0,3,-235,-273,274,0,0,0,0,3,-233,-274,275,0,0,0,0,3,-231,-275,276,0,0,0,0,3,-229,-276,277,0,0,0,0,3,-227,-277,278,0,0,0,0,3,-225,-278,279,0,0,0,0,3,-223,-279,280,0,0,0,0,3,-221,-280,281,0,0,0,0,3,-219,-281,282,0,0,0,0,3,-217,-282,283,0,0,0,0,3,-215,-283,284,0,0,0,0,3,-213,-284,285,0,0,0,0,3,-211,-285,286,0,0,0,0,3,-209,-286,287,0,0,0,0,3,-207,-287,288,0,0,0,0,3,-205,-288,289,0,0,0,0,3,-203,-289,290,0,0,0,0,3,-201,-290,291,0,0,0,0,3,-199,-291,292,0,0,0,0,3,-197,-292,293,0,0,0,0,3,-195,-293,294,0,0,0,0,3,-193,-294,295,0,0,0,0,3,-191,-295,296,0,0,0,0,3,-189,-296,297,0,0,0,0,3,-187,-297,298,0,0,0,0,3,-185,-298,299,0,0,0,0,3,-183,-299,300,0,0,0,0,3,-181,-300,301,0,0,0,0,3,-179,-301,302,0,0,0,0,3,-177,-302,303,0,0,0,0,3,-175,-303,304,0,0,0,0,3,-173,-304,305,0,0,0,0,3,-171,-305,306,0,0,0,0,3,-169,-306,307,0,0,0,0,3,-167,-307,-165,0,0,0,0,3,-3,308,-308};
//const int difficulty = 60; const int memory_nodes = 7000; const int clocks = 37000; const int program[] = {3,2,3,-1,0,0,0,0,3,4,5,-2,0,0,0,0,3,-4,6,7,0,0,0,0,62,-6,8,9,0,0,0,0,3,-8,10,11,0,0,0,0,3,-7,-10,12,0,0,0,0,3,13,14,-12,0,0,0,0,4,15,16,-13,0,0,0,0,5,17,18,-15,0,0,0,0,6,19,20,-17,0,0,0,0,7,21,22,-19,0,0,0,0,8,23,24,-21,0,0,0,0,9,25,26,-23,0,0,0,0,10,27,28,-25,0,0,0,0,11,29,30,-27,0,0,0,0,12,31,32,-29,0,0,0,0,13,33,34,-31,0,0,0,0,14,35,36,-33,0,0,0,0,15,37,38,-35,0,0,0,0,16,39,40,-37,0,0,0,0,17,41,42,-39,0,0,0,0,18,43,44,-41,0,0,0,0,19,45,46,-43,0,0,0,0,20,47,48,-45,0,0,0,0,21,49,50,-47,0,0,0,0,22,51,52,-49,0,0,0,0,23,53,54,-51,0,0,0,0,24,55,56,-53,0,0,0,0,25,57,58,-55,0,0,0,0,26,59,60,-57,0,0,0,0,27,61,62,-59,0,0,0,0,28,63,64,-61,0,0,0,0,29,65,66,-63,0,0,0,0,30,67,68,-65,0,0,0,0,31,69,70,-67,0,0,0,0,32,71,72,-69,0,0,0,0,33,73,74,-71,0,0,0,0,34,75,76,-73,0,0,0,0,35,77,78,-75,0,0,0,0,36,79,80,-77,0,0,0,0,37,81,82,-79,0,0,0,0,38,83,84,-81,0,0,0,0,39,85,86,-83,0,0,0,0,40,87,88,-85,0,0,0,0,41,89,90,-87,0,0,0,0,42,91,92,-89,0,0,0,0,43,93,94,-91,0,0,0,0,44,95,96,-93,0,0,0,0,45,97,98,-95,0,0,0,0,46,99,100,-97,0,0,0,0,47,101,102,-99,0,0,0,0,48,103,104,-101,0,0,0,0,49,105,106,-103,0,0,0,0,50,107,108,-105,0,0,0,0,51,109,110,-107,0,0,0,0,52,111,112,-109,0,0,0,0,53,113,114,-111,0,0,0,0,54,115,116,-113,0,0,0,0,55,117,118,-115,0,0,0,0,56,119,120,-117,0,0,0,0,57,121,122,-119,0,0,0,0,58,123,124,-121,0,0,0,0,59,125,126,-123,0,0,0,0,60,127,128,-125,0,0,0,0,61,-9,129,-127,0,0,0,0,3,-129,-11,130,0,0,0,0,3,-128,-130,131,0,0,0,0,3,-126,-131,132,0,0,0,0,3,-124,-132,133,0,0,0,0,3,-122,-133,134,0,0,0,0,3,-120,-134,135,0,0,0,0,3,-118,-135,136,0,0,0,0,3,-116,-136,137,0,0,0,0,3,-114,-137,138,0,0,0,0,3,-112,-138,139,0,0,0,0,3,-110,-139,140,0,0,0,0,3,-108,-140,141,0,0,0,0,3,-106,-141,142,0,0,0,0,3,-104,-142,143,0,0,0,0,3,-102,-143,144,0,0,0,0,3,-100,-144,145,0,0,0,0,3,-98,-145,146,0,0,0,0,3,-96,-146,147,0,0,0,0,3,-94,-147,148,0,0,0,0,3,-92,-148,149,0,0,0,0,3,-90,-149,150,0,0,0,0,3,-88,-150,151,0,0,0,0,3,-86,-151,152,0,0,0,0,3,-84,-152,153,0,0,0,0,3,-82,-153,154,0,0,0,0,3,-80,-154,155,0,0,0,0,3,-78,-155,156,0,0,0,0,3,-76,-156,157,0,0,0,0,3,-74,-157,158,0,0,0,0,3,-72,-158,159,0,0,0,0,3,-70,-159,160,0,0,0,0,3,-68,-160,161,0,0,0,0,3,-66,-161,162,0,0,0,0,3,-64,-162,163,0,0,0,0,3,-62,-163,164,0,0,0,0,3,-60,-164,165,0,0,0,0,3,-58,-165,166,0,0,0,0,3,-56,-166,167,0,0,0,0,3,-54,-167,168,0,0,0,0,3,-52,-168,169,0,0,0,0,3,-50,-169,170,0,0,0,0,3,-48,-170,171,0,0,0,0,3,-46,-171,172,0,0,0,0,3,-44,-172,173,0,0,0,0,3,-42,-173,174,0,0,0,0,3,-40,-174,175,0,0,0,0,3,-38,-175,176,0,0,0,0,3,-36,-176,177,0,0,0,0,3,-34,-177,178,0,0,0,0,3,-32,-178,179,0,0,0,0,3,-30,-179,180,0,0,0,0,3,-28,-180,181,0,0,0,0,3,-26,-181,182,0,0,0,0,3,-24,-182,183,0,0,0,0,3,-22,-183,184,0,0,0,0,3,-20,-184,185,0,0,0,0,3,-18,-185,186,0,0,0,0,3,-16,-186,-14,0,0,0,0,3,-5,187,188,0,0,0,0,121,-187,189,190,0,0,0,0,3,-189,191,192,0,0,0,0,3,-188,-191,193,0,0,0,0,3,194,195,-193,0,0,0,0,63,196,197,-194,0,0,0,0,64,198,199,-196,0,0,0,0,65,200,201,-198,0,0,0,0,66,202,203,-200,0,0,0,0,67,204,205,-202,0,0,0,0,68,206,207,-204,0,0,0,0,69,208,209,-206,0,0,0,0,70,210,211,-208,0,0,0,0,71,212,213,-210,0,0,0,0,72,214,215,-212,0,0,0,0,73,216,217,-214,0,0,0,0,74,218,219,-216,0,0,0,0,75,220,221,-218,0,0,0,0,76,222,223,-220,0,0,0,0,77,224,225,-222,0,0,0,0,78,226,227,-224,0,0,0,0,79,228,229,-226,0,0,0,0,80,230,231,-228,0,0,0,0,81,232,233,-230,0,0,0,0,82,234,235,-232,0,0,0,0,83,236,237,-234,0,0,0,0,84,238,239,-236,0,0,0,0,85,240,241,-238,0,0,0,0,86,242,243,-240,0,0,0,0,87,244,245,-242,0,0,0,0,88,246,247,-244,0,0,0,0,89,248,249,-246,0,0,0,0,90,250,251,-248,0,0,0,0,91,252,253,-250,0,0,0,0,92,254,255,-252,0,0,0,0,93,256,257,-254,0,0,0,0,94,258,259,-256,0,0,0,0,95,260,261,-258,0,0,0,0,96,262,263,-260,0,0,0,0,97,264,265,-262,0,0,0,0,98,266,267,-264,0,0,0,0,99,268,269,-266,0,0,0,0,100,270,271,-268,0,0,0,0,101,272,273,-270,0,0,0,0,102,274,275,-272,0,0,0,0,103,276,277,-274,0,0,0,0,104,278,279,-276,0,0,0,0,105,280,281,-278,0,0,0,0,106,282,283,-280,0,0,0,0,107,284,285,-282,0,0,0,0,108,286,287,-284,0,0,0,0,109,288,289,-286,0,0,0,0,110,290,291,-288,0,0,0,0,111,292,293,-290,0,0,0,0,112,294,295,-292,0,0,0,0,113,296,297,-294,0,0,0,0,114,298,299,-296,0,0,0,0,115,300,301,-298,0,0,0,0,116,302,303,-300,0,0,0,0,117,304,305,-302,0,0,0,0,118,306,307,-304,0,0,0,0,119,308,309,-306,0,0,0,0,120,-190,310,-308,0,0,0,0,3,-310,-192,311,0,0,0,0,3,-309,-311,312,0,0,0,0,3,-307,-312,313,0,0,0,0,3,-305,-313,314,0,0,0,0,3,-303,-314,315,0,0,0,0,3,-301,-315,316,0,0,0,0,3,-299,-316,317,0,0,0,0,3,-297,-317,318,0,0,0,0,3,-295,-318,319,0,0,0,0,3,-293,-319,320,0,0,0,0,3,-291,-320,321,0,0,0,0,3,-289,-321,322,0,0,0,0,3,-287,-322,323,0,0,0,0,3,-285,-323,324,0,0,0,0,3,-283,-324,325,0,0,0,0,3,-281,-325,326,0,0,0,0,3,-279,-326,327,0,0,0,0,3,-277,-327,328,0,0,0,0,3,-275,-328,329,0,0,0,0,3,-273,-329,330,0,0,0,0,3,-271,-330,331,0,0,0,0,3,-269,-331,332,0,0,0,0,3,-267,-332,333,0,0,0,0,3,-265,-333,334,0,0,0,0,3,-263,-334,335,0,0,0,0,3,-261,-335,336,0,0,0,0,3,-259,-336,337,0,0,0,0,3,-257,-337,338,0,0,0,0,3,-255,-338,339,0,0,0,0,3,-253,-339,340,0,0,0,0,3,-251,-340,341,0,0,0,0,3,-249,-341,342,0,0,0,0,3,-247,-342,343,0,0,0,0,3,-245,-343,344,0,0,0,0,3,-243,-344,345,0,0,0,0,3,-241,-345,346,0,0,0,0,3,-239,-346,347,0,0,0,0,3,-237,-347,348,0,0,0,0,3,-235,-348,349,0,0,0,0,3,-233,-349,350,0,0,0,0,3,-231,-350,351,0,0,0,0,3,-229,-351,352,0,0,0,0,3,-227,-352,353,0,0,0,0,3,-225,-353,354,0,0,0,0,3,-223,-354,355,0,0,0,0,3,-221,-355,356,0,0,0,0,3,-219,-356,357,0,0,0,0,3,-217,-357,358,0,0,0,0,3,-215,-358,359,0,0,0,0,3,-213,-359,360,0,0,0,0,3,-211,-360,361,0,0,0,0,3,-209,-361,362,0,0,0,0,3,-207,-362,363,0,0,0,0,3,-205,-363,364,0,0,0,0,3,-203,-364,365,0,0,0,0,3,-201,-365,366,0,0,0,0,3,-199,-366,367,0,0,0,0,3,-197,-367,-195,0,0,0,0,3,-3,368,-368};
//const int difficulty = 70; const int memory_nodes = 9000; const int clocks = 50000; const int program[] = {3,2,3,-1,0,0,0,0,3,4,5,-2,0,0,0,0,3,-4,6,7,0,0,0,0,72,-6,8,9,0,0,0,0,3,-8,10,11,0,0,0,0,3,-7,-10,12,0,0,0,0,3,13,14,-12,0,0,0,0,4,15,16,-13,0,0,0,0,5,17,18,-15,0,0,0,0,6,19,20,-17,0,0,0,0,7,21,22,-19,0,0,0,0,8,23,24,-21,0,0,0,0,9,25,26,-23,0,0,0,0,10,27,28,-25,0,0,0,0,11,29,30,-27,0,0,0,0,12,31,32,-29,0,0,0,0,13,33,34,-31,0,0,0,0,14,35,36,-33,0,0,0,0,15,37,38,-35,0,0,0,0,16,39,40,-37,0,0,0,0,17,41,42,-39,0,0,0,0,18,43,44,-41,0,0,0,0,19,45,46,-43,0,0,0,0,20,47,48,-45,0,0,0,0,21,49,50,-47,0,0,0,0,22,51,52,-49,0,0,0,0,23,53,54,-51,0,0,0,0,24,55,56,-53,0,0,0,0,25,57,58,-55,0,0,0,0,26,59,60,-57,0,0,0,0,27,61,62,-59,0,0,0,0,28,63,64,-61,0,0,0,0,29,65,66,-63,0,0,0,0,30,67,68,-65,0,0,0,0,31,69,70,-67,0,0,0,0,32,71,72,-69,0,0,0,0,33,73,74,-71,0,0,0,0,34,75,76,-73,0,0,0,0,35,77,78,-75,0,0,0,0,36,79,80,-77,0,0,0,0,37,81,82,-79,0,0,0,0,38,83,84,-81,0,0,0,0,39,85,86,-83,0,0,0,0,40,87,88,-85,0,0,0,0,41,89,90,-87,0,0,0,0,42,91,92,-89,0,0,0,0,43,93,94,-91,0,0,0,0,44,95,96,-93,0,0,0,0,45,97,98,-95,0,0,0,0,46,99,100,-97,0,0,0,0,47,101,102,-99,0,0,0,0,48,103,104,-101,0,0,0,0,49,105,106,-103,0,0,0,0,50,107,108,-105,0,0,0,0,51,109,110,-107,0,0,0,0,52,111,112,-109,0,0,0,0,53,113,114,-111,0,0,0,0,54,115,116,-113,0,0,0,0,55,117,118,-115,0,0,0,0,56,119,120,-117,0,0,0,0,57,121,122,-119,0,0,0,0,58,123,124,-121,0,0,0,0,59,125,126,-123,0,0,0,0,60,127,128,-125,0,0,0,0,61,129,130,-127,0,0,0,0,62,131,132,-129,0,0,0,0,63,133,134,-131,0,0,0,0,64,135,136,-133,0,0,0,0,65,137,138,-135,0,0,0,0,66,139,140,-137,0,0,0,0,67,141,142,-139,0,0,0,0,68,143,144,-141,0,0,0,0,69,145,146,-143,0,0,0,0,70,147,148,-145,0,0,0,0,71,-9,149,-147,0,0,0,0,3,-149,-11,150,0,0,0,0,3,-148,-150,151,0,0,0,0,3,-146,-151,152,0,0,0,0,3,-144,-152,153,0,0,0,0,3,-142,-153,154,0,0,0,0,3,-140,-154,155,0,0,0,0,3,-138,-155,156,0,0,0,0,3,-136,-156,157,0,0,0,0,3,-134,-157,158,0,0,0,0,3,-132,-158,159,0,0,0,0,3,-130,-159,160,0,0,0,0,3,-128,-160,161,0,0,0,0,3,-126,-161,162,0,0,0,0,3,-124,-162,163,0,0,0,0,3,-122,-163,164,0,0,0,0,3,-120,-164,165,0,0,0,0,3,-118,-165,166,0,0,0,0,3,-116,-166,167,0,0,0,0,3,-114,-167,168,0,0,0,0,3,-112,-168,169,0,0,0,0,3,-110,-169,170,0,0,0,0,3,-108,-170,171,0,0,0,0,3,-106,-171,172,0,0,0,0,3,-104,-172,173,0,0,0,0,3,-102,-173,174,0,0,0,0,3,-100,-174,175,0,0,0,0,3,-98,-175,176,0,0,0,0,3,-96,-176,177,0,0,0,0,3,-94,-177,178,0,0,0,0,3,-92,-178,179,0,0,0,0,3,-90,-179,180,0,0,0,0,3,-88,-180,181,0,0,0,0,3,-86,-181,182,0,0,0,0,3,-84,-182,183,0,0,0,0,3,-82,-183,184,0,0,0,0,3,-80,-184,185,0,0,0,0,3,-78,-185,186,0,0,0,0,3,-76,-186,187,0,0,0,0,3,-74,-187,188,0,0,0,0,3,-72,-188,189,0,0,0,0,3,-70,-189,190,0,0,0,0,3,-68,-190,191,0,0,0,0,3,-66,-191,192,0,0,0,0,3,-64,-192,193,0,0,0,0,3,-62,-193,194,0,0,0,0,3,-60,-194,195,0,0,0,0,3,-58,-195,196,0,0,0,0,3,-56,-196,197,0,0,0,0,3,-54,-197,198,0,0,0,0,3,-52,-198,199,0,0,0,0,3,-50,-199,200,0,0,0,0,3,-48,-200,201,0,0,0,0,3,-46,-201,202,0,0,0,0,3,-44,-202,203,0,0,0,0,3,-42,-203,204,0,0,0,0,3,-40,-204,205,0,0,0,0,3,-38,-205,206,0,0,0,0,3,-36,-206,207,0,0,0,0,3,-34,-207,208,0,0,0,0,3,-32,-208,209,0,0,0,0,3,-30,-209,210,0,0,0,0,3,-28,-210,211,0,0,0,0,3,-26,-211,212,0,0,0,0,3,-24,-212,213,0,0,0,0,3,-22,-213,214,0,0,0,0,3,-20,-214,215,0,0,0,0,3,-18,-215,216,0,0,0,0,3,-16,-216,-14,0,0,0,0,3,-5,217,218,0,0,0,0,141,-217,219,220,0,0,0,0,3,-219,221,222,0,0,0,0,3,-218,-221,223,0,0,0,0,3,224,225,-223,0,0,0,0,73,226,227,-224,0,0,0,0,74,228,229,-226,0,0,0,0,75,230,231,-228,0,0,0,0,76,232,233,-230,0,0,0,0,77,234,235,-232,0,0,0,0,78,236,237,-234,0,0,0,0,79,238,239,-236,0,0,0,0,80,240,241,-238,0,0,0,0,81,242,243,-240,0,0,0,0,82,244,245,-242,0,0,0,0,83,246,247,-244,0,0,0,0,84,248,249,-246,0,0,0,0,85,250,251,-248,0,0,0,0,86,252,253,-250,0,0,0,0,87,254,255,-252,0,0,0,0,88,256,257,-254,0,0,0,0,89,258,259,-256,0,0,0,0,90,260,261,-258,0,0,0,0,91,262,263,-260,0,0,0,0,92,264,265,-262,0,0,0,0,93,266,267,-264,0,0,0,0,94,268,269,-266,0,0,0,0,95,270,271,-268,0,0,0,0,96,272,273,-270,0,0,0,0,97,274,275,-272,0,0,0,0,98,276,277,-274,0,0,0,0,99,278,279,-276,0,0,0,0,100,280,281,-278,0,0,0,0,101,282,283,-280,0,0,0,0,102,284,285,-282,0,0,0,0,103,286,287,-284,0,0,0,0,104,288,289,-286,0,0,0,0,105,290,291,-288,0,0,0,0,106,292,293,-290,0,0,0,0,107,294,295,-292,0,0,0,0,108,296,297,-294,0,0,0,0,109,298,299,-296,0,0,0,0,110,300,301,-298,0,0,0,0,111,302,303,-300,0,0,0,0,112,304,305,-302,0,0,0,0,113,306,307,-304,0,0,0,0,114,308,309,-306,0,0,0,0,115,310,311,-308,0,0,0,0,116,312,313,-310,0,0,0,0,117,314,315,-312,0,0,0,0,118,316,317,-314,0,0,0,0,119,318,319,-316,0,0,0,0,120,320,321,-318,0,0,0,0,121,322,323,-320,0,0,0,0,122,324,325,-322,0,0,0,0,123,326,327,-324,0,0,0,0,124,328,329,-326,0,0,0,0,125,330,331,-328,0,0,0,0,126,332,333,-330,0,0,0,0,127,334,335,-332,0,0,0,0,128,336,337,-334,0,0,0,0,129,338,339,-336,0,0,0,0,130,340,341,-338,0,0,0,0,131,342,343,-340,0,0,0,0,132,344,345,-342,0,0,0,0,133,346,347,-344,0,0,0,0,134,348,349,-346,0,0,0,0,135,350,351,-348,0,0,0,0,136,352,353,-350,0,0,0,0,137,354,355,-352,0,0,0,0,138,356,357,-354,0,0,0,0,139,358,359,-356,0,0,0,0,140,-220,360,-358,0,0,0,0,3,-360,-222,361,0,0,0,0,3,-359,-361,362,0,0,0,0,3,-357,-362,363,0,0,0,0,3,-355,-363,364,0,0,0,0,3,-353,-364,365,0,0,0,0,3,-351,-365,366,0,0,0,0,3,-349,-366,367,0,0,0,0,3,-347,-367,368,0,0,0,0,3,-345,-368,369,0,0,0,0,3,-343,-369,370,0,0,0,0,3,-341,-370,371,0,0,0,0,3,-339,-371,372,0,0,0,0,3,-337,-372,373,0,0,0,0,3,-335,-373,374,0,0,0,0,3,-333,-374,375,0,0,0,0,3,-331,-375,376,0,0,0,0,3,-329,-376,377,0,0,0,0,3,-327,-377,378,0,0,0,0,3,-325,-378,379,0,0,0,0,3,-323,-379,380,0,0,0,0,3,-321,-380,381,0,0,0,0,3,-319,-381,382,0,0,0,0,3,-317,-382,383,0,0,0,0,3,-315,-383,384,0,0,0,0,3,-313,-384,385,0,0,0,0,3,-311,-385,386,0,0,0,0,3,-309,-386,387,0,0,0,0,3,-307,-387,388,0,0,0,0,3,-305,-388,389,0,0,0,0,3,-303,-389,390,0,0,0,0,3,-301,-390,391,0,0,0,0,3,-299,-391,392,0,0,0,0,3,-297,-392,393,0,0,0,0,3,-295,-393,394,0,0,0,0,3,-293,-394,395,0,0,0,0,3,-291,-395,396,0,0,0,0,3,-289,-396,397,0,0,0,0,3,-287,-397,398,0,0,0,0,3,-285,-398,399,0,0,0,0,3,-283,-399,400,0,0,0,0,3,-281,-400,401,0,0,0,0,3,-279,-401,402,0,0,0,0,3,-277,-402,403,0,0,0,0,3,-275,-403,404,0,0,0,0,3,-273,-404,405,0,0,0,0,3,-271,-405,406,0,0,0,0,3,-269,-406,407,0,0,0,0,3,-267,-407,408,0,0,0,0,3,-265,-408,409,0,0,0,0,3,-263,-409,410,0,0,0,0,3,-261,-410,411,0,0,0,0,3,-259,-411,412,0,0,0,0,3,-257,-412,413,0,0,0,0,3,-255,-413,414,0,0,0,0,3,-253,-414,415,0,0,0,0,3,-251,-415,416,0,0,0,0,3,-249,-416,417,0,0,0,0,3,-247,-417,418,0,0,0,0,3,-245,-418,419,0,0,0,0,3,-243,-419,420,0,0,0,0,3,-241,-420,421,0,0,0,0,3,-239,-421,422,0,0,0,0,3,-237,-422,423,0,0,0,0,3,-235,-423,424,0,0,0,0,3,-233,-424,425,0,0,0,0,3,-231,-425,426,0,0,0,0,3,-229,-426,427,0,0,0,0,3,-227,-427,-225,0,0,0,0,3,-3,428,-428};

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap4(int* a, int* b){
    for (int i=0; i<4; ++i)
        swap(a+i, b+i);
};

void erase(int* a){
    for (int i=0; i<4; ++i)
        a[i] = 0;
};

void rewrite(int* a, int* b, int* c){
    // Full block
    if (!(a[0] || b[0] || c[0]) || (a[0] && b[0] && c[0]))
        return;

    // Move
    if (!(a[0] || b[0]) || (a[0] && b[0]))
        swap4(&b[0], &c[0]);

    // Duplicate
    if (a[0] < 0 && b[0] == 0)
        swap(&a[1], &a[2]),
        b[0] = -a[0], b[1] = a[3], a[0] *= -1,
        b[2] = a[2] + (a[2]>0?2:-1),
        a[3] = a[2] + (a[2]>0?1:-2),
        b[3] = a[2] + (a[2]>0?3:-3);

    // Nothing to do
    if (!(a[0]>0 && !b[0] && c[0]>0))
        return;

    // Passthrough
    if (   (a[1] >  0 && c[1]  < 0)  
        || (a[1] >  0 && a[0] == 1)  
        || (c[0] == 1 && c[1]  < 0)){
        swap4(a, c);
        for (int i=1; i<=3; ++i)
            a[i] *= a[i]==-c[1] || a[i]==-c[2] || a[i]==-c[3] ? -1 : 1;
        for (int i=1; i<=3; ++i)
            c[i] *= c[i]== a[1] || c[i]== a[2] || c[i]== a[3] ? -1 : 1;
    };

    // Substitute
    for (int n=0; n<2; ++n){
        int* x = n ? c : a;
        int* y = n ? a : c;
        for (int i=1; i<=3; ++i){
            if (x[0] == 1 && x[1] == -y[i]){
                y[i] = x[2];
                erase(x);
                if (y[2] == -y[3] && y[2] < 0)
                    swap(&y[2], &y[3]);
                if (y[1] == -y[2])
                    erase(y);
            };
        };
    };

    // React
    if (a[0] > 1 && c[0] > 1 && a[1] == -c[1]){
        if (a[0] == c[0])
            a[0] = 1, a[1] = a[2], a[2] = c[2],
            c[0] = 1, c[1] = a[3], c[2] = c[3],
            a[3] = 0, c[3] = 0;
        else
            swap(a, c),
            a[0] *= -1,
            c[0] *= -1,
            a[1] = (a[1]*1103515245+12345)&0x7fffffff, // PRNG
            c[1] = -a[1];
    };
};

void process(int *mem, int len, int j){
    for (int i=j; i<len-2; i+=3)
        rewrite(mem+i*4, mem+i*4+4, mem+i*4+8);
};

void print(int *S, int len){
    for (int j=0; j<4; ++j){
        for (int i=j; i<len*4; i+=4){
                 if (!j && S[i]<-1) printf("DD|");
            else if (!j && S[i]==1) printf("%%%%|");
            else if (S[i]>0) printf("%02x>", S[i]%256);
            else if (S[i]<0) printf("%02x<", (-S[i])%256);
            else if (j<3) printf("  |");
            else printf("__|");
        };
        printf("\n");
    };
};


// Change to 1 to visualize the progress of the memory.
int memory[memory_nodes*4];
const int visualize = 0; // Change to 1 to visualize the progress of the memory.
const int memory_ints = memory_nodes * 4;
const int memory_size = memory_ints * sizeof(int);
const int program_nodes = sizeof program / sizeof(int) / 4;

int main(){
    for (int i=0; i < memory_ints; ++i)
        memory[i] = i < program_nodes*4 ? program[i] : 0;

    printf("First 40 nodes of the input memory: \n");
    print(memory, 40);
    for (int i=0; i<clocks; ++i)
        for (int j=0; j<3; ++j)
            process(memory, memory_nodes, j);

    printf("First 40 nodes of the output memory:\n");
    print(memory, 40);
    printf("If the slice above has exactly 4 numbers and the last 2 are equal, the alogirthm probably works.");
}