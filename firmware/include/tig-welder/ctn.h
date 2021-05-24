// This file is part of the tig-welder project
// (https://github.com/cclienti/tig-welder)
// Copyright (c) 2021 Christophe Clienti
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#ifndef TIG_WELDER_CTN_H
#define TIG_WELDER_CTN_H


#include <cstdint>


static const std::uint16_t TEMP_LUT [] =
{
	26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880,
	26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880,
	26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880,
	26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880, 26880,
	26880, 26880, 26880, 26880, 26796, 26713, 26631, 26551, 26471, 26393, 26316, 26240, 26164, 26091, 26018, 25946,
	25875, 25806, 25736, 25668, 25600, 25532, 25465, 25399, 25334, 25269, 25205, 25142, 25080, 25019, 24960, 24901,
	24843, 24787, 24732, 24677, 24624, 24572, 24520, 24469, 24419, 24369, 24320, 24271, 24223, 24175, 24128, 24082,
	24036, 23991, 23946, 23901, 23857, 23812, 23768, 23724, 23680, 23635, 23591, 23547, 23504, 23460, 23416, 23373,
	23329, 23287, 23244, 23202, 23161, 23120, 23079, 23040, 23000, 22961, 22923, 22885, 22847, 22810, 22774, 22738,
	22702, 22667, 22633, 22598, 22564, 22531, 22497, 22464, 22432, 22400, 22368, 22336, 22305, 22274, 22243, 22213,
	22183, 22154, 22125, 22096, 22068, 22039, 22011, 21983, 21955, 21927, 21899, 21871, 21843, 21815, 21787, 21760,
	21732, 21704, 21677, 21649, 21621, 21594, 21567, 21539, 21512, 21485, 21457, 21430, 21403, 21376, 21350, 21323,
	21297, 21271, 21245, 21220, 21194, 21169, 21144, 21120, 21095, 21071, 21047, 21023, 20999, 20976, 20952, 20929,
	20906, 20884, 20861, 20839, 20817, 20796, 20774, 20753, 20731, 20710, 20688, 20667, 20646, 20625, 20604, 20583,
	20562, 20541, 20521, 20500, 20480, 20459, 20439, 20418, 20398, 20378, 20357, 20337, 20317, 20297, 20277, 20258,
	20238, 20218, 20199, 20179, 20160, 20140, 20121, 20101, 20082, 20063, 20044, 20025, 20006, 19987, 19969, 19950,
	19931, 19913, 19894, 19876, 19858, 19840, 19821, 19803, 19785, 19767, 19749, 19732, 19714, 19696, 19679, 19661,
	19644, 19626, 19609, 19592, 19575, 19558, 19541, 19524, 19507, 19490, 19474, 19457, 19440, 19424, 19407, 19391,
	19375, 19358, 19342, 19326, 19310, 19294, 19278, 19262, 19246, 19231, 19215, 19200, 19184, 19168, 19153, 19138,
	19122, 19107, 19092, 19077, 19062, 19047, 19032, 19017, 19003, 18988, 18973, 18959, 18944, 18930, 18915, 18901,
	18887, 18873, 18859, 18845, 18831, 18817, 18803, 18789, 18775, 18761, 18747, 18734, 18720, 18706, 18693, 18679,
	18666, 18652, 18639, 18626, 18612, 18599, 18586, 18573, 18560, 18546, 18533, 18520, 18507, 18494, 18482, 18469,
	18456, 18443, 18430, 18418, 18405, 18393, 18380, 18368, 18355, 18343, 18330, 18318, 18306, 18294, 18281, 18269,
	18257, 18245, 18233, 18221, 18209, 18197, 18185, 18174, 18162, 18150, 18138, 18126, 18115, 18103, 18091, 18080,
	18068, 18056, 18045, 18033, 18022, 18010, 17999, 17988, 17976, 17965, 17953, 17942, 17931, 17920, 17908, 17897,
	17886, 17875, 17864, 17852, 17841, 17830, 17819, 17808, 17797, 17786, 17775, 17765, 17754, 17743, 17732, 17721,
	17710, 17700, 17689, 17678, 17668, 17657, 17647, 17636, 17625, 17615, 17604, 17594, 17583, 17573, 17563, 17552,
	17542, 17532, 17521, 17511, 17501, 17490, 17480, 17470, 17460, 17450, 17439, 17429, 17419, 17409, 17399, 17389,
	17379, 17369, 17359, 17349, 17339, 17329, 17319, 17309, 17299, 17289, 17280, 17270, 17260, 17250, 17240, 17231,
	17221, 17211, 17201, 17192, 17182, 17172, 17163, 17153, 17144, 17134, 17125, 17115, 17106, 17096, 17087, 17077,
	17068, 17058, 17049, 17040, 17030, 17021, 17012, 17003, 16993, 16984, 16975, 16966, 16956, 16947, 16938, 16929,
	16920, 16911, 16902, 16893, 16884, 16875, 16866, 16857, 16848, 16839, 16830, 16821, 16812, 16804, 16795, 16786,
	16777, 16768, 16760, 16751, 16742, 16734, 16725, 16716, 16708, 16699, 16691, 16682, 16673, 16665, 16656, 16648,
	16640, 16631, 16623, 16614, 16606, 16598, 16589, 16581, 16573, 16564, 16556, 16548, 16540, 16531, 16523, 16515,
	16507, 16499, 16491, 16483, 16475, 16467, 16459, 16451, 16443, 16435, 16427, 16419, 16411, 16403, 16395, 16388,
	16380, 16372, 16364, 16356, 16349, 16341, 16333, 16326, 16318, 16310, 16303, 16295, 16288, 16280, 16272, 16265,
	16257, 16250, 16242, 16235, 16227, 16220, 16212, 16205, 16197, 16190, 16182, 16175, 16168, 16160, 16153, 16145,
	16138, 16131, 16123, 16116, 16109, 16101, 16094, 16087, 16079, 16072, 16065, 16057, 16050, 16043, 16036, 16028,
	16021, 16014, 16007, 16000, 15992, 15985, 15978, 15971, 15964, 15956, 15949, 15942, 15935, 15928, 15921, 15914,
	15907, 15900, 15893, 15886, 15879, 15872, 15865, 15858, 15851, 15844, 15837, 15830, 15823, 15816, 15809, 15802,
	15795, 15788, 15781, 15774, 15767, 15760, 15754, 15747, 15740, 15733, 15726, 15719, 15713, 15706, 15699, 15692,
	15686, 15679, 15672, 15665, 15659, 15652, 15645, 15639, 15632, 15625, 15618, 15612, 15605, 15599, 15592, 15585,
	15579, 15572, 15565, 15559, 15552, 15546, 15539, 15533, 15526, 15520, 15513, 15507, 15500, 15494, 15487, 15481,
	15474, 15468, 15461, 15455, 15448, 15442, 15436, 15429, 15423, 15416, 15410, 15404, 15397, 15391, 15385, 15378,
	15372, 15366, 15360, 15353, 15347, 15341, 15334, 15328, 15322, 15316, 15309, 15303, 15297, 15291, 15285, 15279,
	15272, 15266, 15260, 15254, 15248, 15242, 15236, 15230, 15223, 15217, 15211, 15205, 15199, 15193, 15187, 15181,
	15175, 15169, 15163, 15157, 15151, 15145, 15139, 15133, 15127, 15121, 15115, 15110, 15104, 15098, 15092, 15086,
	15080, 15074, 15068, 15063, 15057, 15051, 15045, 15039, 15034, 15028, 15022, 15016, 15011, 15005, 14999, 14993,
	14988, 14982, 14976, 14970, 14965, 14959, 14953, 14948, 14942, 14936, 14931, 14925, 14919, 14914, 14908, 14902,
	14897, 14891, 14885, 14880, 14874, 14869, 14863, 14857, 14852, 14846, 14841, 14835, 14829, 14824, 14818, 14813,
	14807, 14802, 14796, 14791, 14785, 14780, 14774, 14769, 14763, 14758, 14752, 14747, 14741, 14736, 14730, 14725,
	14720, 14714, 14709, 14703, 14698, 14692, 14687, 14682, 14676, 14671, 14665, 14660, 14655, 14649, 14644, 14639,
	14633, 14628, 14623, 14617, 14612, 14607, 14601, 14596, 14591, 14585, 14580, 14575, 14570, 14564, 14559, 14554,
	14549, 14543, 14538, 14533, 14528, 14522, 14517, 14512, 14507, 14502, 14496, 14491, 14486, 14481, 14476, 14471,
	14465, 14460, 14455, 14450, 14445, 14440, 14435, 14430, 14425, 14419, 14414, 14409, 14404, 14399, 14394, 14389,
	14384, 14379, 14374, 14369, 14364, 14359, 14354, 14349, 14344, 14339, 14334, 14329, 14324, 14319, 14314, 14309,
	14304, 14299, 14294, 14289, 14284, 14279, 14274, 14269, 14264, 14259, 14254, 14249, 14244, 14239, 14234, 14230,
	14225, 14220, 14215, 14210, 14205, 14200, 14195, 14190, 14186, 14181, 14176, 14171, 14166, 14161, 14156, 14152,
	14147, 14142, 14137, 14132, 14127, 14123, 14118, 14113, 14108, 14103, 14099, 14094, 14089, 14084, 14080, 14075,
	14070, 14065, 14060, 14056, 14051, 14046, 14041, 14037, 14032, 14027, 14023, 14018, 14013, 14008, 14004, 13999,
	13994, 13990, 13985, 13980, 13976, 13971, 13966, 13962, 13957, 13952, 13948, 13943, 13938, 13934, 13929, 13925,
	13920, 13915, 13911, 13906, 13901, 13897, 13892, 13888, 13883, 13879, 13874, 13869, 13865, 13860, 13856, 13851,
	13847, 13842, 13838, 13833, 13828, 13824, 13819, 13815, 13810, 13806, 13801, 13797, 13792, 13788, 13783, 13779,
	13774, 13770, 13765, 13761, 13757, 13752, 13748, 13743, 13739, 13734, 13730, 13725, 13721, 13717, 13712, 13708,
	13703, 13699, 13695, 13690, 13686, 13681, 13677, 13673, 13668, 13664, 13659, 13655, 13651, 13646, 13642, 13637,
	13633, 13629, 13624, 13620, 13616, 13611, 13607, 13603, 13598, 13594, 13590, 13585, 13581, 13577, 13572, 13568,
	13564, 13559, 13555, 13551, 13546, 13542, 13538, 13533, 13529, 13525, 13520, 13516, 13512, 13508, 13503, 13499,
	13495, 13491, 13486, 13482, 13478, 13473, 13469, 13465, 13461, 13456, 13452, 13448, 13444, 13440, 13435, 13431,
	13427, 13423, 13418, 13414, 13410, 13406, 13402, 13397, 13393, 13389, 13385, 13381, 13376, 13372, 13368, 13364,
	13360, 13355, 13351, 13347, 13343, 13339, 13335, 13330, 13326, 13322, 13318, 13314, 13310, 13306, 13301, 13297,
	13293, 13289, 13285, 13281, 13277, 13273, 13268, 13264, 13260, 13256, 13252, 13248, 13244, 13240, 13236, 13232,
	13228, 13223, 13219, 13215, 13211, 13207, 13203, 13199, 13195, 13191, 13187, 13183, 13179, 13175, 13171, 13167,
	13163, 13159, 13155, 13151, 13147, 13143, 13138, 13134, 13130, 13126, 13122, 13118, 13114, 13110, 13106, 13102,
	13098, 13095, 13091, 13087, 13083, 13079, 13075, 13071, 13067, 13063, 13059, 13055, 13051, 13047, 13043, 13039,
	13035, 13031, 13027, 13023, 13019, 13015, 13011, 13008, 13004, 13000, 12996, 12992, 12988, 12984, 12980, 12976,
	12972, 12968, 12965, 12961, 12957, 12953, 12949, 12945, 12941, 12937, 12933, 12930, 12926, 12922, 12918, 12914,
	12910, 12906, 12903, 12899, 12895, 12891, 12887, 12883, 12879, 12876, 12872, 12868, 12864, 12860, 12857, 12853,
	12849, 12845, 12841, 12837, 12834, 12830, 12826, 12822, 12818, 12815, 12811, 12807, 12803, 12800, 12796, 12792,
	12788, 12784, 12781, 12777, 12773, 12769, 12766, 12762, 12758, 12754, 12751, 12747, 12743, 12739, 12736, 12732,
	12728, 12724, 12721, 12717, 12713, 12709, 12706, 12702, 12698, 12695, 12691, 12687, 12684, 12680, 12676, 12672,
	12669, 12665, 12661, 12658, 12654, 12650, 12647, 12643, 12639, 12636, 12632, 12628, 12625, 12621, 12617, 12614,
	12610, 12606, 12603, 12599, 12595, 12592, 12588, 12585, 12581, 12577, 12574, 12570, 12566, 12563, 12559, 12556,
	12552, 12548, 12545, 12541, 12538, 12534, 12530, 12527, 12523, 12520, 12516, 12513, 12509, 12505, 12502, 12498,
	12495, 12491, 12488, 12484, 12480, 12477, 12473, 12470, 12466, 12463, 12459, 12456, 12452, 12449, 12445, 12441,
	12438, 12434, 12431, 12427, 12424, 12420, 12417, 12413, 12410, 12406, 12403, 12399, 12396, 12392, 12389, 12385,
	12382, 12378, 12375, 12371, 12368, 12364, 12361, 12357, 12354, 12350, 12347, 12343, 12340, 12336, 12333, 12329,
	12326, 12322, 12319, 12315, 12312, 12308, 12305, 12301, 12298, 12294, 12291, 12287, 12284, 12280, 12277, 12273,
	12270, 12266, 12263, 12259, 12256, 12253, 12249, 12246, 12242, 12239, 12235, 12232, 12228, 12225, 12221, 12218,
	12215, 12211, 12208, 12204, 12201, 12197, 12194, 12190, 12187, 12184, 12180, 12177, 12173, 12170, 12166, 12163,
	12160, 12156, 12153, 12149, 12146, 12142, 12139, 12136, 12132, 12129, 12125, 12122, 12118, 12115, 12112, 12108,
	12105, 12101, 12098, 12095, 12091, 12088, 12084, 12081, 12078, 12074, 12071, 12067, 12064, 12061, 12057, 12054,
	12050, 12047, 12044, 12040, 12037, 12034, 12030, 12027, 12023, 12020, 12017, 12013, 12010, 12007, 12003, 12000,
	11996, 11993, 11990, 11986, 11983, 11980, 11976, 11973, 11970, 11966, 11963, 11960, 11956, 11953, 11950, 11946,
	11943, 11939, 11936, 11933, 11929, 11926, 11923, 11919, 11916, 11913, 11909, 11906, 11903, 11899, 11896, 11893,
	11890, 11886, 11883, 11880, 11876, 11873, 11870, 11866, 11863, 11860, 11856, 11853, 11850, 11846, 11843, 11840,
	11837, 11833, 11830, 11827, 11823, 11820, 11817, 11813, 11810, 11807, 11804, 11800, 11797, 11794, 11790, 11787,
	11784, 11781, 11777, 11774, 11771, 11767, 11764, 11761, 11758, 11754, 11751, 11748, 11745, 11741, 11738, 11735,
	11732, 11728, 11725, 11722, 11719, 11715, 11712, 11709, 11706, 11702, 11699, 11696, 11693, 11689, 11686, 11683,
	11680, 11676, 11673, 11670, 11667, 11663, 11660, 11657, 11654, 11651, 11647, 11644, 11641, 11638, 11634, 11631,
	11628, 11625, 11622, 11618, 11615, 11612, 11609, 11606, 11602, 11599, 11596, 11593, 11590, 11586, 11583, 11580,
	11577, 11574, 11570, 11567, 11564, 11561, 11558, 11554, 11551, 11548, 11545, 11542, 11539, 11535, 11532, 11529,
	11526, 11523, 11520, 11516, 11513, 11510, 11507, 11504, 11501, 11497, 11494, 11491, 11488, 11485, 11482, 11478,
	11475, 11472, 11469, 11466, 11463, 11460, 11456, 11453, 11450, 11447, 11444, 11441, 11438, 11434, 11431, 11428,
	11425, 11422, 11419, 11416, 11413, 11409, 11406, 11403, 11400, 11397, 11394, 11391, 11388, 11384, 11381, 11378,
	11375, 11372, 11369, 11366, 11363, 11360, 11357, 11353, 11350, 11347, 11344, 11341, 11338, 11335, 11332, 11329,
	11326, 11323, 11319, 11316, 11313, 11310, 11307, 11304, 11301, 11298, 11295, 11292, 11289, 11286, 11283, 11280,
	11276, 11273, 11270, 11267, 11264, 11261, 11258, 11255, 11252, 11249, 11246, 11243, 11240, 11237, 11234, 11231,
	11228, 11225, 11222, 11218, 11215, 11212, 11209, 11206, 11203, 11200, 11197, 11194, 11191, 11188, 11185, 11182,
	11179, 11176, 11173, 11170, 11167, 11164, 11161, 11158, 11155, 11152, 11149, 11146, 11143, 11140, 11137, 11134,
	11131, 11128, 11125, 11122, 11119, 11116, 11113, 11110, 11107, 11104, 11101, 11098, 11095, 11092, 11089, 11086,
	11083, 11080, 11077, 11074, 11071, 11068, 11065, 11062, 11059, 11056, 11053, 11050, 11047, 11044, 11041, 11038,
	11035, 11032, 11029, 11026, 11023, 11020, 11017, 11014, 11011, 11008, 11005, 11002, 10999, 10996, 10993, 10990,
	10987, 10984, 10981, 10978, 10975, 10972, 10969, 10966, 10963, 10960, 10957, 10954, 10951, 10948, 10945, 10942,
	10939, 10936, 10933, 10930, 10927, 10924, 10921, 10918, 10915, 10912, 10909, 10906, 10903, 10900, 10897, 10894,
	10891, 10888, 10885, 10882, 10880, 10877, 10874, 10871, 10868, 10865, 10862, 10859, 10856, 10853, 10850, 10847,
	10844, 10841, 10838, 10835, 10832, 10829, 10826, 10823, 10820, 10817, 10814, 10811, 10808, 10805, 10803, 10800,
	10797, 10794, 10791, 10788, 10785, 10782, 10779, 10776, 10773, 10770, 10767, 10764, 10761, 10758, 10755, 10752,
	10749, 10747, 10744, 10741, 10738, 10735, 10732, 10729, 10726, 10723, 10720, 10717, 10714, 10711, 10708, 10705,
	10702, 10700, 10697, 10694, 10691, 10688, 10685, 10682, 10679, 10676, 10673, 10670, 10667, 10664, 10661, 10659,
	10656, 10653, 10650, 10647, 10644, 10641, 10638, 10635, 10632, 10629, 10626, 10623, 10621, 10618, 10615, 10612,
	10609, 10606, 10603, 10600, 10597, 10594, 10591, 10588, 10586, 10583, 10580, 10577, 10574, 10571, 10568, 10565,
	10562, 10559, 10556, 10554, 10551, 10548, 10545, 10542, 10539, 10536, 10533, 10530, 10527, 10525, 10522, 10519,
	10516, 10513, 10510, 10507, 10504, 10501, 10498, 10496, 10493, 10490, 10487, 10484, 10481, 10478, 10475, 10472,
	10470, 10467, 10464, 10461, 10458, 10455, 10452, 10449, 10446, 10443, 10441, 10438, 10435, 10432, 10429, 10426,
	10423, 10420, 10418, 10415, 10412, 10409, 10406, 10403, 10400, 10397, 10394, 10392, 10389, 10386, 10383, 10380,
	10377, 10374, 10371, 10369, 10366, 10363, 10360, 10357, 10354, 10351, 10348, 10346, 10343, 10340, 10337, 10334,
	10331, 10328, 10325, 10323, 10320, 10317, 10314, 10311, 10308, 10305, 10302, 10300, 10297, 10294, 10291, 10288,
	10285, 10282, 10280, 10277, 10274, 10271, 10268, 10265, 10262, 10260, 10257, 10254, 10251, 10248, 10245, 10242,
	10240, 10237, 10234, 10231, 10228, 10225, 10222, 10220, 10217, 10214, 10211, 10208, 10205, 10202, 10200, 10197,
	10194, 10191, 10188, 10185, 10182, 10180, 10177, 10174, 10171, 10168, 10165, 10163, 10160, 10157, 10154, 10151,
	10148, 10145, 10143, 10140, 10137, 10134, 10131, 10128, 10126, 10123, 10120, 10117, 10114, 10111, 10109, 10106,
	10103, 10100, 10097, 10094, 10091, 10089, 10086, 10083, 10080, 10077, 10074, 10072, 10069, 10066, 10063, 10060,
	10057, 10055, 10052, 10049, 10046, 10043, 10041, 10038, 10035, 10032, 10029, 10026, 10024, 10021, 10018, 10015,
	10012, 10009, 10007, 10004, 10001, 9998, 9995, 9993, 9990, 9987, 9984, 9981, 9978, 9976, 9973, 9970,
	9967, 9964, 9962, 9959, 9956, 9953, 9950, 9947, 9945, 9942, 9939, 9936, 9933, 9931, 9928, 9925,
	9922, 9919, 9917, 9914, 9911, 9908, 9905, 9903, 9900, 9897, 9894, 9891, 9888, 9886, 9883, 9880,
	9877, 9874, 9872, 9869, 9866, 9863, 9860, 9858, 9855, 9852, 9849, 9846, 9844, 9841, 9838, 9835,
	9832, 9830, 9827, 9824, 9821, 9818, 9815, 9813, 9810, 9807, 9804, 9801, 9799, 9796, 9793, 9790,
	9787, 9785, 9782, 9779, 9776, 9773, 9771, 9768, 9765, 9762, 9759, 9757, 9754, 9751, 9748, 9745,
	9743, 9740, 9737, 9734, 9731, 9728, 9726, 9723, 9720, 9717, 9714, 9712, 9709, 9706, 9703, 9700,
	9698, 9695, 9692, 9689, 9686, 9684, 9681, 9678, 9675, 9672, 9670, 9667, 9664, 9661, 9658, 9656,
	9653, 9650, 9647, 9644, 9642, 9639, 9636, 9633, 9630, 9628, 9625, 9622, 9619, 9616, 9614, 9611,
	9608, 9605, 9602, 9600, 9597, 9594, 9591, 9588, 9585, 9583, 9580, 9577, 9574, 9571, 9569, 9566,
	9563, 9560, 9557, 9555, 9552, 9549, 9546, 9543, 9541, 9538, 9535, 9532, 9529, 9527, 9524, 9521,
	9518, 9515, 9513, 9510, 9507, 9504, 9501, 9499, 9496, 9493, 9490, 9487, 9485, 9482, 9479, 9476,
	9473, 9471, 9468, 9465, 9462, 9459, 9457, 9454, 9451, 9448, 9445, 9443, 9440, 9437, 9434, 9431,
	9429, 9426, 9423, 9420, 9417, 9415, 9412, 9409, 9406, 9403, 9401, 9398, 9395, 9392, 9389, 9387,
	9384, 9381, 9378, 9375, 9373, 9370, 9367, 9364, 9361, 9359, 9356, 9353, 9350, 9347, 9345, 9342,
	9339, 9336, 9333, 9331, 9328, 9325, 9322, 9319, 9317, 9314, 9311, 9308, 9305, 9303, 9300, 9297,
	9294, 9291, 9289, 9286, 9283, 9280, 9277, 9275, 9272, 9269, 9266, 9263, 9261, 9258, 9255, 9252,
	9249, 9247, 9244, 9241, 9238, 9235, 9233, 9230, 9227, 9224, 9221, 9219, 9216, 9213, 9210, 9207,
	9205, 9202, 9199, 9196, 9193, 9191, 9188, 9185, 9182, 9179, 9177, 9174, 9171, 9168, 9165, 9163,
	9160, 9157, 9154, 9151, 9148, 9146, 9143, 9140, 9137, 9134, 9132, 9129, 9126, 9123, 9120, 9118,
	9115, 9112, 9109, 9106, 9103, 9101, 9098, 9095, 9092, 9089, 9087, 9084, 9081, 9078, 9075, 9072,
	9070, 9067, 9064, 9061, 9058, 9056, 9053, 9050, 9047, 9044, 9041, 9039, 9036, 9033, 9030, 9027,
	9025, 9022, 9019, 9016, 9013, 9010, 9008, 9005, 9002, 8999, 8996, 8993, 8991, 8988, 8985, 8982,
	8979, 8976, 8974, 8971, 8968, 8965, 8962, 8960, 8957, 8954, 8951, 8948, 8945, 8943, 8940, 8937,
	8934, 8931, 8928, 8926, 8923, 8920, 8917, 8914, 8911, 8909, 8906, 8903, 8900, 8897, 8894, 8892,
	8889, 8886, 8883, 8880, 8877, 8874, 8872, 8869, 8866, 8863, 8860, 8857, 8855, 8852, 8849, 8846,
	8843, 8840, 8838, 8835, 8832, 8829, 8826, 8823, 8820, 8818, 8815, 8812, 8809, 8806, 8803, 8801,
	8798, 8795, 8792, 8789, 8786, 8783, 8781, 8778, 8775, 8772, 8769, 8766, 8764, 8761, 8758, 8755,
	8752, 8749, 8746, 8744, 8741, 8738, 8735, 8732, 8729, 8726, 8724, 8721, 8718, 8715, 8712, 8709,
	8707, 8704, 8701, 8698, 8695, 8692, 8689, 8687, 8684, 8681, 8678, 8675, 8672, 8669, 8667, 8664,
	8661, 8658, 8655, 8652, 8649, 8646, 8644, 8641, 8638, 8635, 8632, 8629, 8626, 8624, 8621, 8618,
	8615, 8612, 8609, 8606, 8604, 8601, 8598, 8595, 8592, 8589, 8586, 8583, 8581, 8578, 8575, 8572,
	8569, 8566, 8563, 8560, 8558, 8555, 8552, 8549, 8546, 8543, 8540, 8537, 8534, 8532, 8529, 8526,
	8523, 8520, 8517, 8514, 8511, 8509, 8506, 8503, 8500, 8497, 8494, 8491, 8488, 8485, 8482, 8480,
	8477, 8474, 8471, 8468, 8465, 8462, 8459, 8456, 8454, 8451, 8448, 8445, 8442, 8439, 8436, 8433,
	8430, 8427, 8424, 8422, 8419, 8416, 8413, 8410, 8407, 8404, 8401, 8398, 8395, 8392, 8390, 8387,
	8384, 8381, 8378, 8375, 8372, 8369, 8366, 8363, 8360, 8357, 8355, 8352, 8349, 8346, 8343, 8340,
	8337, 8334, 8331, 8328, 8325, 8322, 8320, 8317, 8314, 8311, 8308, 8305, 8302, 8299, 8296, 8293,
	8290, 8287, 8284, 8281, 8278, 8276, 8273, 8270, 8267, 8264, 8261, 8258, 8255, 8252, 8249, 8246,
	8243, 8240, 8237, 8234, 8231, 8228, 8226, 8223, 8220, 8217, 8214, 8211, 8208, 8205, 8202, 8199,
	8196, 8193, 8190, 8187, 8184, 8181, 8178, 8175, 8172, 8169, 8167, 8164, 8161, 8158, 8155, 8152,
	8149, 8146, 8143, 8140, 8137, 8134, 8131, 8128, 8125, 8122, 8119, 8116, 8113, 8110, 8107, 8104,
	8101, 8098, 8095, 8092, 8089, 8086, 8083, 8081, 8078, 8075, 8072, 8069, 8066, 8063, 8060, 8057,
	8054, 8051, 8048, 8045, 8042, 8039, 8036, 8033, 8030, 8027, 8024, 8021, 8018, 8015, 8012, 8009,
	8006, 8003, 8000, 7997, 7994, 7991, 7988, 7985, 7982, 7979, 7976, 7973, 7970, 7967, 7964, 7961,
	7958, 7955, 7952, 7949, 7946, 7943, 7940, 7937, 7934, 7931, 7928, 7925, 7922, 7919, 7916, 7913,
	7910, 7907, 7904, 7901, 7898, 7895, 7892, 7889, 7885, 7882, 7879, 7876, 7873, 7870, 7867, 7864,
	7861, 7858, 7855, 7852, 7849, 7846, 7843, 7840, 7837, 7834, 7831, 7828, 7825, 7821, 7818, 7815,
	7812, 7809, 7806, 7803, 7800, 7797, 7794, 7791, 7788, 7785, 7782, 7779, 7775, 7772, 7769, 7766,
	7763, 7760, 7757, 7754, 7751, 7748, 7745, 7742, 7738, 7735, 7732, 7729, 7726, 7723, 7720, 7717,
	7714, 7711, 7707, 7704, 7701, 7698, 7695, 7692, 7689, 7686, 7683, 7680, 7676, 7673, 7670, 7667,
	7664, 7661, 7658, 7655, 7651, 7648, 7645, 7642, 7639, 7636, 7633, 7630, 7626, 7623, 7620, 7617,
	7614, 7611, 7608, 7604, 7601, 7598, 7595, 7592, 7589, 7586, 7582, 7579, 7576, 7573, 7570, 7567,
	7563, 7560, 7557, 7554, 7551, 7548, 7545, 7541, 7538, 7535, 7532, 7529, 7526, 7522, 7519, 7516,
	7513, 7510, 7506, 7503, 7500, 7497, 7494, 7491, 7487, 7484, 7481, 7478, 7475, 7471, 7468, 7465,
	7462, 7459, 7455, 7452, 7449, 7446, 7443, 7439, 7436, 7433, 7430, 7427, 7423, 7420, 7417, 7414,
	7411, 7407, 7404, 7401, 7398, 7395, 7391, 7388, 7385, 7382, 7378, 7375, 7372, 7369, 7366, 7362,
	7359, 7356, 7353, 7349, 7346, 7343, 7340, 7336, 7333, 7330, 7327, 7323, 7320, 7317, 7314, 7310,
	7307, 7304, 7301, 7297, 7294, 7291, 7287, 7284, 7281, 7278, 7274, 7271, 7268, 7264, 7261, 7258,
	7255, 7251, 7248, 7245, 7241, 7238, 7235, 7231, 7228, 7225, 7221, 7218, 7215, 7212, 7208, 7205,
	7202, 7198, 7195, 7192, 7188, 7185, 7182, 7178, 7175, 7172, 7168, 7165, 7161, 7158, 7155, 7151,
	7148, 7145, 7141, 7138, 7135, 7131, 7128, 7124, 7121, 7118, 7114, 7111, 7108, 7104, 7101, 7097,
	7094, 7091, 7087, 7084, 7080, 7077, 7074, 7070, 7067, 7063, 7060, 7057, 7053, 7050, 7046, 7043,
	7040, 7036, 7033, 7029, 7026, 7022, 7019, 7015, 7012, 7009, 7005, 7002, 6998, 6995, 6991, 6988,
	6984, 6981, 6978, 6974, 6971, 6967, 6964, 6960, 6957, 6953, 6950, 6946, 6943, 6939, 6936, 6932,
	6929, 6925, 6922, 6918, 6915, 6911, 6908, 6904, 6901, 6897, 6894, 6890, 6887, 6883, 6880, 6876,
	6873, 6869, 6866, 6862, 6859, 6855, 6852, 6848, 6845, 6841, 6838, 6834, 6831, 6827, 6823, 6820,
	6816, 6813, 6809, 6806, 6802, 6799, 6795, 6791, 6788, 6784, 6781, 6777, 6774, 6770, 6766, 6763,
	6759, 6756, 6752, 6749, 6745, 6741, 6738, 6734, 6731, 6727, 6723, 6720, 6716, 6713, 6709, 6705,
	6702, 6698, 6695, 6691, 6687, 6684, 6680, 6676, 6673, 6669, 6665, 6662, 6658, 6654, 6651, 6647,
	6644, 6640, 6636, 6633, 6629, 6625, 6621, 6618, 6614, 6610, 6607, 6603, 6599, 6596, 6592, 6588,
	6585, 6581, 6577, 6573, 6570, 6566, 6562, 6559, 6555, 6551, 6547, 6544, 6540, 6536, 6532, 6529,
	6525, 6521, 6517, 6514, 6510, 6506, 6502, 6499, 6495, 6491, 6487, 6483, 6480, 6476, 6472, 6468,
	6464, 6461, 6457, 6453, 6449, 6445, 6442, 6438, 6434, 6430, 6426, 6423, 6419, 6415, 6411, 6407,
	6403, 6400, 6396, 6392, 6388, 6384, 6380, 6376, 6373, 6369, 6365, 6361, 6357, 6353, 6349, 6345,
	6342, 6338, 6334, 6330, 6326, 6322, 6318, 6314, 6310, 6306, 6303, 6299, 6295, 6291, 6287, 6283,
	6279, 6275, 6271, 6267, 6263, 6259, 6255, 6251, 6247, 6243, 6240, 6236, 6232, 6228, 6224, 6220,
	6216, 6212, 6208, 6204, 6200, 6196, 6192, 6188, 6184, 6180, 6176, 6172, 6168, 6164, 6160, 6156,
	6152, 6148, 6144, 6140, 6136, 6132, 6128, 6124, 6120, 6115, 6111, 6107, 6103, 6099, 6095, 6091,
	6087, 6083, 6079, 6075, 6071, 6067, 6063, 6058, 6054, 6050, 6046, 6042, 6038, 6034, 6030, 6026,
	6021, 6017, 6013, 6009, 6005, 6001, 5996, 5992, 5988, 5984, 5980, 5975, 5971, 5967, 5963, 5959,
	5954, 5950, 5946, 5942, 5938, 5933, 5929, 5925, 5921, 5916, 5912, 5908, 5903, 5899, 5895, 5891,
	5886, 5882, 5878, 5873, 5869, 5865, 5860, 5856, 5852, 5847, 5843, 5839, 5834, 5830, 5826, 5821,
	5817, 5812, 5808, 5804, 5799, 5795, 5790, 5786, 5782, 5777, 5773, 5768, 5764, 5760, 5755, 5751,
	5746, 5742, 5737, 5733, 5728, 5724, 5719, 5715, 5710, 5706, 5701, 5697, 5692, 5688, 5683, 5679,
	5674, 5670, 5665, 5661, 5656, 5651, 5647, 5642, 5638, 5633, 5629, 5624, 5619, 5615, 5610, 5606,
	5601, 5596, 5592, 5587, 5583, 5578, 5573, 5569, 5564, 5559, 5555, 5550, 5545, 5541, 5536, 5531,
	5527, 5522, 5517, 5513, 5508, 5503, 5498, 5494, 5489, 5484, 5480, 5475, 5470, 5465, 5461, 5456,
	5451, 5446, 5441, 5437, 5432, 5427, 5422, 5417, 5413, 5408, 5403, 5398, 5393, 5388, 5383, 5379,
	5374, 5369, 5364, 5359, 5354, 5349, 5344, 5339, 5334, 5329, 5324, 5319, 5314, 5309, 5304, 5299,
	5294, 5289, 5284, 5279, 5274, 5269, 5264, 5259, 5254, 5249, 5244, 5239, 5234, 5229, 5223, 5218,
	5213, 5208, 5203, 5198, 5193, 5187, 5182, 5177, 5172, 5167, 5161, 5156, 5151, 5146, 5141, 5135,
	5130, 5125, 5120, 5114, 5109, 5104, 5098, 5093, 5088, 5082, 5077, 5072, 5066, 5061, 5056, 5050,
	5045, 5039, 5034, 5029, 5023, 5018, 5012, 5007, 5002, 4996, 4991, 4985, 4980, 4974, 4969, 4963,
	4958, 4952, 4947, 4941, 4936, 4930, 4925, 4919, 4913, 4908, 4902, 4897, 4891, 4886, 4880, 4874,
	4869, 4863, 4857, 4852, 4846, 4840, 4835, 4829, 4823, 4818, 4812, 4806, 4801, 4795, 4789, 4783,
	4778, 4772, 4766, 4760, 4754, 4748, 4743, 4737, 4731, 4725, 4719, 4713, 4707, 4701, 4695, 4689,
	4683, 4677, 4671, 4665, 4659, 4653, 4647, 4641, 4635, 4629, 4623, 4617, 4611, 4605, 4599, 4592,
	4586, 4580, 4574, 4568, 4561, 4555, 4549, 4543, 4536, 4530, 4524, 4518, 4511, 4505, 4499, 4492,
	4486, 4480, 4473, 4467, 4460, 4454, 4447, 4441, 4435, 4428, 4422, 4415, 4409, 4402, 4395, 4389,
	4382, 4376, 4369, 4363, 4356, 4349, 4343, 4336, 4329, 4323, 4316, 4309, 4303, 4296, 4289, 4282,
	4276, 4269, 4262, 4255, 4249, 4242, 4235, 4228, 4221, 4214, 4207, 4201, 4194, 4187, 4180, 4173,
	4166, 4159, 4152, 4145, 4138, 4131, 4124, 4117, 4110, 4102, 4095, 4088, 4081, 4074, 4066, 4059,
	4052, 4044, 4037, 4030, 4022, 4015, 4008, 4000, 3993, 3985, 3978, 3970, 3963, 3955, 3948, 3940,
	3932, 3925, 3917, 3909, 3902, 3894, 3886, 3879, 3871, 3863, 3855, 3847, 3840, 3832, 3824, 3816,
	3808, 3800, 3792, 3784, 3776, 3768, 3760, 3752, 3744, 3736, 3727, 3719, 3711, 3703, 3695, 3686,
	3678, 3670, 3662, 3653, 3645, 3636, 3628, 3620, 3611, 3603, 3594, 3586, 3577, 3569, 3560, 3552,
	3543, 3535, 3526, 3517, 3508, 3500, 3491, 3482, 3473, 3464, 3455, 3446, 3437, 3428, 3419, 3410,
	3401, 3392, 3382, 3373, 3364, 3354, 3345, 3336, 3326, 3317, 3307, 3297, 3288, 3278, 3268, 3259,
	3249, 3239, 3229, 3219, 3209, 3200, 3189, 3179, 3169, 3159, 3149, 3139, 3129, 3118, 3108, 3098,
	3087, 3077, 3067, 3056, 3046, 3035, 3024, 3014, 3003, 2992, 2982, 2971, 2960, 2949, 2938, 2927,
	2916, 2905, 2894, 2883, 2872, 2861, 2849, 2838, 2827, 2815, 2803, 2792, 2780, 2768, 2757, 2745,
	2733, 2721, 2709, 2697, 2685, 2672, 2660, 2648, 2635, 2623, 2610, 2598, 2585, 2572, 2560, 2547,
	2534, 2521, 2508, 2495, 2481, 2468, 2455, 2442, 2428, 2415, 2401, 2388, 2374, 2360, 2347, 2333,
	2319, 2305, 2291, 2277, 2263, 2248, 2234, 2220, 2205, 2190, 2175, 2160, 2145, 2130, 2114, 2099,
	2083, 2067, 2052, 2035, 2019, 2003, 1987, 1970, 1953, 1936, 1920, 1902, 1885, 1868, 1850, 1833,
	1815, 1797, 1779, 1761, 1743, 1724, 1706, 1687, 1669, 1650, 1631, 1611, 1592, 1573, 1553, 1533,
	1513, 1493, 1472, 1451, 1431, 1410, 1388, 1367, 1345, 1324, 1302, 1280, 1257, 1235, 1212, 1189,
	1166, 1143, 1119, 1096, 1072, 1048, 1023, 999, 974, 949, 924, 898, 871, 844, 816, 788,
	759, 730, 700, 670, 640, 608, 577, 544, 512, 478, 445, 410, 375, 340, 304, 268,
	231, 194, 156, 118, 79, 39, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

constexpr int lut_size(void)
{
	constexpr int lut_size = sizeof(TEMP_LUT) / sizeof(TEMP_LUT[0]);
	static_assert(lut_size == 4096,
	              "Missing elements in the TEMP_LUT initialization, expecting 4096 elements");
	return lut_size;
}

static int get_temp_int(std::uint16_t adc_value) {
	int address = adc_value & (lut_size() - 1);
	return (TEMP_LUT[address] >> 7) - 55;
}

static float get_temp_float(std::uint16_t adc_value) {
	int address = adc_value & (lut_size() - 1);
	return (TEMP_LUT[address] / 128.0) - 55;
}



#endif
