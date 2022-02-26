#include "TFile.h"
#include "TH1.h"
#include "TString.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TGraph2D.h"

#include <vector>
#include <iostream>
#include <string>
#include <cfloat>

using std::vector;
using std::pair;

static bool useCorrection = false;

static bool useB1 = true;

static TString inputPath = "/nfs/dust/atlas/user/sargyrop/ROOT/2HDMATF/";

static vector<TString> regions_B1 =  {"2tag2pjet_150_200ptv",
				      "2tag2pjet_200_350ptv",
				      "2tag2pjet_350_500ptv",
				      "2tag1pfatjet_0addtag_500_750ptv",
				      "2tag1pfatjet_0addtag_750ptv"
				     }; 
				     
static vector<TString> regions_B2 = {"2tag2pjet_150_200ptv",
				     "2tag2pjet_200_350ptv",
				     "2tag2pjet_350_500ptv",
				     "2tag1pfatjet_0addtag_500_750ptv",
				     "2tag1pfatjet_0addtag_750ptv",
				     "3ptag2pjet_150_200ptv",
				     "3ptag2pjet_200_350ptv",
				     "3ptag2pjet_350_500ptv",
				     "2tag1pfatjet_1paddtag_500_750ptv",
				     "2tag1pfatjet_1paddtag_750ptv"
				    };

static vector<TString> regions = (useB1) ? regions_B1 : regions_B2;

// Sample - xsec (in pb)
static vector<pair<TString, float>> samples_1200 = {
					       {"200000_monoHbb_mA1200_ma100_mX10",     0.01214},
					       {"200001_monoHbb_mA1200_ma200_mX10",     0.010460},
					       {"200002_monoHbb_mA1200_ma300_mX10",     0.009442},
					       {"200003_monoHbb_mA1200_ma400_mX10",     0.007767},
					       {"200004_monoHbb_mA1200_ma500_mX10",     0.005736},
					       {"200005_monoHbb_mA1200_ma600_mX10",     0.004157},
					       {"200006_monoHbb_mA1200_ma100_mX50",     0.058830},
					       {"200007_monoHbb_mA1200_ma200_mX50",     0.010460},
					       {"200008_monoHbb_mA1200_ma300_mX50",     0.009411},
					       {"200009_monoHbb_mA1200_ma400_mX50",     0.007715},
					       {"200010_monoHbb_mA1200_ma500_mX50",     0.005711},
					       {"200011_monoHbb_mA1200_ma600_mX50",     0.004143},
					       {"200012_monoHbb_mA1200_ma200_mX100",    0.031800},
					       {"200013_monoHbb_mA1200_ma300_mX100",    0.009364},
					       {"200014_monoHbb_mA1200_ma400_mX100",    0.007516},
					       {"200015_monoHbb_mA1200_ma500_mX100",    0.005619},
					       {"200016_monoHbb_mA1200_ma600_mX100",    0.004105},
					       {"200017_monoHbb_mA1200_ma300_mX150",    0.014410},
					       {"200018_monoHbb_mA1200_ma400_mX150",    0.007179},
					       {"200019_monoHbb_mA1200_ma500_mX150",    0.005430},
					       {"200020_monoHbb_mA1200_ma600_mX150",    0.004022},
					       {"200021_monoHbb_mA1200_ma400_mX200",    0.002927},
					       {"200022_monoHbb_mA1200_ma500_mX200",    0.005097},
					       {"200023_monoHbb_mA1200_ma600_mX200",    0.003874},
					       {"200024_monoHbb_mA1200_ma500_mX250",    0.001885},
					       {"200025_monoHbb_mA1200_ma600_mX250",    0.003603},
					       {"200026_monoHbb_mA1200_ma600_mX300",    0.001312},
// 					     {"200027_monoHbb_mA1200_ma700_mX10",     0.002782},
// 					     {"200028_monoHbb_mA1200_ma700_mX50",     0.002777},
// 					     {"200029_monoHbb_mA1200_ma700_mX100",    0.002760},
// 					     {"200030_monoHbb_mA1200_ma700_mX150",    0.002723},
// 					     {"200031_monoHbb_mA1200_ma700_mX200",    0.002661},
// 					     {"200032_monoHbb_mA1200_ma700_mX250",    0.002552},
// 					     {"200033_monoHbb_mA1200_ma700_mX300",    0.002355},
// 					     {"200034_monoHbb_mA1200_ma700_mX350",    0.000855},
// 					     {"200035_monoHbb_mA1200_ma700_mX400",    0.000017},
					       {"200036_monoHbb_mA1200_ma600_mX350",    0.000034},
					       {"200037_monoHbb_mA1200_ma500_mX300",    0.000055},
					       {"200038_monoHbb_mA1200_ma400_mX250",    0.000080},
					       {"200039_monoHbb_mA1200_ma300_mX200",    0.000111},
					       {"200040_monoHbb_mA1200_ma200_mX150",    0.000149},
					       {"200041_monoHbb_mA1200_ma100_mX75",     0.000308},
					       {"200042_monoHbb_mA1200_ma50_mX10",      0.013150},
					       {"200043_monoHbb_mA1200_ma50_mX25",      0.071680},
 					       {"200044_monoHbb_mA1200_ma50_mX30",      0.000673},
					       {"200045_monoHbb_mA1200_ma70_mX10",	0.01279},
					       {"200046_monoHbb_mA1200_ma70_mX35",	0.06669},
					       {"200047_monoHbb_mA1200_ma70_mX50",	0.0004246},
					      };
					      
static vector<pair<TString, float>> samples_1000 = {
 					       {"400000_monoHbb_mA1000_ma100_mX10",  0.053030},
 					       {"400001_monoHbb_mA1000_ma200_mX10",  0.034330},
 					       {"400002_monoHbb_mA1000_ma300_mX10",  0.024680},
 					       {"400003_monoHbb_mA1000_ma400_mX10",  0.018280},
 					       {"400004_monoHbb_mA1000_ma500_mX10",  0.011510},
 					       {"400005_monoHbb_mA1000_ma600_mX10",  0.006722},
 					       {"400006_monoHbb_mA1000_ma100_mX50",  0.309700},
 					       {"400007_monoHbb_mA1000_ma200_mX50",  0.033970},
 					       {"400008_monoHbb_mA1000_ma300_mX50",  0.024230},
 					       {"400009_monoHbb_mA1000_ma400_mX50",  0.017990},
 					       {"400010_monoHbb_mA1000_ma500_mX50",  0.011430},
 					       {"400011_monoHbb_mA1000_ma600_mX50",  0.006695},
 					       {"400012_monoHbb_mA1000_ma200_mX100", 0.131600},
 					       {"400013_monoHbb_mA1000_ma300_mX100", 0.023320},
 					       {"400014_monoHbb_mA1000_ma400_mX100", 0.016910},
 					       {"400015_monoHbb_mA1000_ma500_mX100", 0.011140},
 					       {"400016_monoHbb_mA1000_ma600_mX100", 0.006602},
 					       {"400017_monoHbb_mA1000_ma300_mX150", 0.059940},
 					       {"400018_monoHbb_mA1000_ma400_mX150", 0.015600},
 					       {"400019_monoHbb_mA1000_ma500_mX150", 0.010560},
 					       {"400020_monoHbb_mA1000_ma600_mX150", 0.006417},
 					       {"400021_monoHbb_mA1000_ma400_mX200", 0.006461},
 					       {"400022_monoHbb_mA1000_ma500_mX200", 0.009745},
 					       {"400023_monoHbb_mA1000_ma600_mX200", 0.006092},
 					       {"400024_monoHbb_mA1000_ma500_mX250", 0.003651},
 					       {"400025_monoHbb_mA1000_ma600_mX250", 0.005596},
 					       {"400026_monoHbb_mA1000_ma600_mX300", 0.002134},
 					       {"400027_monoHbb_mA1000_ma700_mX10",  0.003222},
 					       {"400028_monoHbb_mA1000_ma700_mX50",  0.003213},
 					       {"400029_monoHbb_mA1000_ma700_mX100", 0.003180},
 					       {"400030_monoHbb_mA1000_ma700_mX150", 0.003117},
 					       {"400031_monoHbb_mA1000_ma700_mX200", 0.003006},
 					       {"400032_monoHbb_mA1000_ma700_mX250", 0.002828},
 					       {"400033_monoHbb_mA1000_ma700_mX300", 0.002556},
 					       {"400034_monoHbb_mA1000_ma700_mX350", 0.000921},
 					       {"400035_monoHbb_mA1000_ma700_mX400", 0.000008},
 					       {"400036_monoHbb_mA1000_ma600_mX350", 0.000022},
 					       {"400037_monoHbb_mA1000_ma500_mX300", 0.000056},
 					       {"400038_monoHbb_mA1000_ma400_mX250", 0.000110},
 					       {"400039_monoHbb_mA1000_ma300_mX200", 0.000180},
 					       {"400040_monoHbb_mA1000_ma200_mX150", 0.000273},
 					       {"400041_monoHbb_mA1000_ma100_mX75",  0.000721},
 					       {"400042_monoHbb_mA1000_ma50_mX10",   0.075750},
 					       {"400043_monoHbb_mA1000_ma50_mX25",   0.491000},
 					       {"400044_monoHbb_mA1000_ma50_mX30",   0.002428}
					      };

static vector<pair<TString, float>> samples_B2 = {
 					       {"320000_monoHbb_mA1000_ma100_mX10_B2" , 0.1288},
 					       {"320001_monoHbb_mA1000_ma200_mX10_B2" , 0.02962},
 					       {"320002_monoHbb_mA1000_ma300_mX10_B2" , 0.01382},
 					       {"320003_monoHbb_mA1000_ma400_mX10_B2" , 0.006614},
 					       {"320004_monoHbb_mA1000_ma500_mX10_B2" , 0.003252},
 					       {"320005_monoHbb_mA1000_ma600_mX10_B2" , 0.001811},
 					       {"320006_monoHbb_mA1000_ma100_mX50_B2" , 0.01384},
 					       {"320007_monoHbb_mA1000_ma200_mX50_B2" , 0.02097},
 					       {"320008_monoHbb_mA1000_ma300_mX50_B2" , 0.01102},
 					       {"320009_monoHbb_mA1000_ma400_mX50_B2" , 0.00605},
 					       {"320010_monoHbb_mA1000_ma500_mX50_B2" , 0.003109},
 					       {"320011_monoHbb_mA1000_ma600_mX50_B2" , 0.001763},
 					       {"320012_monoHbb_mA1000_ma200_mX100_B2" , 0.002274},
 					       {"320013_monoHbb_mA1000_ma300_mX100_B2" , 0.005805},
 					       {"320014_monoHbb_mA1000_ma400_mX100_B2" , 0.004169},
 					       {"320015_monoHbb_mA1000_ma500_mX100_B2" , 0.002607},
 					       {"320016_monoHbb_mA1000_ma600_mX100_B2" , 0.001597},
 					       {"320017_monoHbb_mA1000_ma300_mX150_B2" , 0.00071},
 					       {"320018_monoHbb_mA1000_ma400_mX150_B2" , 0.002281},
 					       {"320019_monoHbb_mA1000_ma500_mX150_B2" , 0.00176},
 					       {"320020_monoHbb_mA1000_ma600_mX150_B2" , 0.001305},
 					       {"320021_monoHbb_mA1000_ma400_mX200_B2" , 0.0003127},
 					       {"320022_monoHbb_mA1000_ma500_mX200_B2" , 0.001002},
 					       {"320023_monoHbb_mA1000_ma600_mX200_B2" , 0.0009002},
 					       {"320024_monoHbb_mA1000_ma500_mX250_B2" , 0.0001452},
 					       {"320025_monoHbb_mA1000_ma600_mX250_B2" , 0.0005339},
 					       {"320026_monoHbb_mA1000_ma600_mX300_B2" , 7.99e-05},
 // 					       {"320027_monoHbb_mA1000_ma700_mX10_B2" , 0.001006},
//  					       {"320028_monoHbb_mA1000_ma700_mX50_B2" , 0.0009878},
//  					       {"320029_monoHbb_mA1000_ma700_mX100_B2" , 0.0009263},
//  					       {"320030_monoHbb_mA1000_ma700_mX150_B2" , 0.0008179},
//  					       {"320031_monoHbb_mA1000_ma700_mX200_B2" , 0.0006578},
//  					       {"320032_monoHbb_mA1000_ma700_mX250_B2" , 0.0004543},
//  					       {"320033_monoHbb_mA1000_ma700_mX300_B2" , 0.0002681},
//  					       {"320034_monoHbb_mA1000_ma700_mX350_B2" , 4.042e-05},
//  					       {"320035_monoHbb_mA1000_ma700_mX400_B2" , 6.588e-06},
 					       {"320036_monoHbb_mA1000_ma600_mX350_B2" , 5.439e-06},
 					       {"320037_monoHbb_mA1000_ma500_mX300_B2" , 5.004e-06},
 					       {"320038_monoHbb_mA1000_ma400_mX250_B2" , 8.358e-06},
 					       {"320039_monoHbb_mA1000_ma300_mX200_B2" , 1.289e-05},
 					       {"320040_monoHbb_mA1000_ma200_mX150_B2" , 2.024e-05},
 					       {"320041_monoHbb_mA1000_ma100_mX75_B2" , 0.000269},
 					       {"320042_monoHbb_mA1000_ma50_mX10_B2" , 0.399},
 					       {"320043_monoHbb_mA1000_ma50_mX25_B2" , 0.05128},
 					       {"320044_monoHbb_mA1000_ma50_mX30_B2" , 0.005561},
					       {"320045_monoHbb_mA1000_ma70_mX10_B2" , 0.249},
					       {"320046_monoHbb_mA1000_ma70_mX35_B2" , 0.02901},
					       {"320047_monoHbb_mA1000_ma70_mX50_B2" , 0.0009875},
					         };


float getBR(float ma, float mx) {
  if (useB1) {
    if (ma == 50) {
      if (mx <100) return 0.0317;
      else return 0.571;
    }
    else if (ma==100) {
      if (mx <100) return 0.58;
      else return 0.571;
    }
    else return 0.571;
  }
  else {
    if (ma == 50) {
      if (mx <100) return 0.013;
      else return 0.571;
    }
    else if (ma==100) {
      if (mx <100) return 0.579;
      else return 0.571;
    }
    else return 0.571;
  }
}


float recoAcc(int mA, int ma, const TString &region) {
  if (mA == 1200) {
    if (ma <= 100) {
      if (region == "2tag2pjet_150_200ptv") {
        return 0.0098;
      } 
      else if (region == "2tag2pjet_200_350ptv") {
        return 0.0701;
      } 
      else if (region == "2tag2pjet_350_500ptv") {
        return 0.0742;
      } 
      else if (region == "2tag1pfatjet_0addtag_500_750ptv") {
        return 0.0534;
      } 
      else if (region == "2tag1pfatjet_0addtag_750ptv") {
        return 0.0012;
      } 
      else return -1;
    } 
    else if (ma == 200) {
      if (region == "2tag2pjet_150_200ptv") {
        return 0.0081;
      } 
      else if (region == "2tag2pjet_200_350ptv") {
        return 0.0681;
      } 
      else if (region == "2tag2pjet_350_500ptv") {
        return 0.0818;
      } 
      else if (region == "2tag1pfatjet_0addtag_500_750ptv") {
        return 0.0537;
      } 
      else if (region == "2tag1pfatjet_0addtag_750ptv") {
        return 0.0006;
      } 
      else return -1;
    }
    else if (ma == 300) {
      if (region == "2tag2pjet_150_200ptv") {
        return 0.0070;
      } 
      else if (region == "2tag2pjet_200_350ptv") {
        return 0.0626;
      } 
      else if (region == "2tag2pjet_350_500ptv") {
        return 0.0844;
      } 
      else if (region == "2tag1pfatjet_0addtag_500_750ptv") {
        return 0.0476;
      } 
      else if (region == "2tag1pfatjet_0addtag_750ptv") {
        return 0.0007;
      } 
      else return -1;
    }
    else if (ma == 400) {
      if (region == "2tag2pjet_150_200ptv") {
        return 0.0086;
      } 
      else if (region == "2tag2pjet_200_350ptv") {
        return 0.0628;
      } 
      else if (region == "2tag2pjet_350_500ptv") {
        return 0.0837;
      } 
      else if (region == "2tag1pfatjet_0addtag_500_750ptv") {
        return 0.0310;
      } 
      else if (region == "2tag1pfatjet_0addtag_750ptv") {
        return 0.0005;
      } 
      else return -1;
    }
    else if (ma == 500) {
      if (region == "2tag2pjet_150_200ptv") {
        return 0.0084;
      } 
      else if (region == "2tag2pjet_200_350ptv") {
        return 0.0753;
      } 
      else if (region == "2tag2pjet_350_500ptv") {
        return 0.0878;
      } 
      else if (region == "2tag1pfatjet_0addtag_500_750ptv") {
        return 0.0207;
      } 
      else if (region == "2tag1pfatjet_0addtag_750ptv") {
        return 0.0006;
      } 
      else return -1;
    }
    // This is taken from 1300,600
    else if (ma == 600) {
      if (region == "2tag2pjet_150_200ptv") {
        return 0.0064;
      } 
      else if (region == "2tag2pjet_200_350ptv") {
        return 0.0720;
      } 
      else if (region == "2tag2pjet_350_500ptv") {
        return 0.0908;
      } 
      else if (region == "2tag1pfatjet_0addtag_500_750ptv") {
        return 0.0306;
      } 
      else if (region == "2tag1pfatjet_0addtag_750ptv") {
        return 0.0006;
      } 
      else return -1;
    }
    else if (ma == 700) { // same as 600
      if (region == "2tag2pjet_150_200ptv") {
        return 0.0064;
      } 
      else if (region == "2tag2pjet_200_350ptv") {
        return 0.0720;
      } 
      else if (region == "2tag2pjet_350_500ptv") {
        return 0.0908;
      } 
      else if (region == "2tag1pfatjet_0addtag_500_750ptv") {
        return 0.0306;
      } 
      else if (region == "2tag1pfatjet_0addtag_750ptv") {
        return 0.0006;
      } 
      else return -1;
    }
    else return -1;
  }
  else if (mA == 1000) {
    if (ma < 100) { // same as mA=1200, ma=100
      if (region == "2tag2pjet_150_200ptv") {
        return 0.0098;
      } 
      else if (region == "2tag2pjet_200_350ptv") {
        return 0.0701;
      } 
      else if (region == "2tag2pjet_350_500ptv") {
        return 0.0742;
      } 
      else if (region == "2tag1pfatjet_0addtag_500_750ptv") {
        return 0.0534;
      } 
      else if (region == "2tag1pfatjet_0addtag_750ptv") {
        return 0.0012;
      } 
      else return -1;
    }
    else if (ma == 100) { // same as ma=150
      if (region == "2tag2pjet_150_200ptv") {
        return 0.0102;
      } 
      else if (region == "2tag2pjet_200_350ptv") {
        return 0.0590;
      } 
      else if (region == "2tag2pjet_350_500ptv") {
        return 0.0607;
      } 
      else if (region == "2tag1pfatjet_0addtag_500_750ptv") {
        return 0.0110;
      } 
      else if (region == "2tag1pfatjet_0addtag_750ptv") {
        return 0.0010;
      } 
      else return -1;
    } 
    else if (ma == 200) { 
      if (region == "2tag2pjet_150_200ptv") {
        return 0.0102;
      } 
      else if (region == "2tag2pjet_200_350ptv") {
        return 0.0690;
      } 
      else if (region == "2tag2pjet_350_500ptv") {
        return 0.0690;
      } 
      else if (region == "2tag1pfatjet_0addtag_500_750ptv") {
        return 0.0108;
      } 
      else if (region == "2tag1pfatjet_0addtag_750ptv") {
        return 0.00001;
      } 
      else return -1;
    }
    else if (ma == 300) {
      if (region == "2tag2pjet_150_200ptv") {
        return 0.0094;
      } 
      else if (region == "2tag2pjet_200_350ptv") {
        return 0.0806;
      } 
      else if (region == "2tag2pjet_350_500ptv") {
        return 0.0713;
      } 
      else if (region == "2tag1pfatjet_0addtag_500_750ptv") {
        return 0.0076;
      } 
      else if (region == "2tag1pfatjet_0addtag_750ptv") {
        return 0.0001;
      } 
      else return -1;
    }
    else if (ma == 400) {
      if (region == "2tag2pjet_150_200ptv") {
        return 0.0100;
      } 
      else if (region == "2tag2pjet_200_350ptv") {
        return 0.0892;
      } 
      else if (region == "2tag2pjet_350_500ptv") {
        return 0.0538;
      } 
      else if (region == "2tag1pfatjet_0addtag_500_750ptv") {
        return 0.00360;
      } 
      else if (region == "2tag1pfatjet_0addtag_750ptv") {
        return 0.0010;
      } 
      else return -1;
    }
    else if (ma == 500) {
      if (region == "2tag2pjet_150_200ptv") {
        return 0.0134;
      } 
      else if (region == "2tag2pjet_200_350ptv") {
        return 0.1057;
      } 
      else if (region == "2tag2pjet_350_500ptv") {
        return 0.0309;
      } 
      else if (region == "2tag1pfatjet_0addtag_500_750ptv") {
        return 0.0018;
      } 
      else if (region == "2tag1pfatjet_0addtag_750ptv") {
        return 0.0001;
      } 
      else return -1;
    }
    else if (ma == 600) {
      if (region == "2tag2pjet_150_200ptv") {
        return 0.0189;
      } 
      else if (region == "2tag2pjet_200_350ptv") {
        return 0.1025;
      } 
      else if (region == "2tag2pjet_350_500ptv") {
        return 0.0093;
      } 
      else if (region == "2tag1pfatjet_0addtag_500_750ptv") {
        return 0.0002;
      } 
      else if (region == "2tag1pfatjet_0addtag_750ptv") {
        return 0.0001;
      } 
      else return -1;
    }
    else if (ma == 700) { // same as 600
      if (region == "2tag2pjet_150_200ptv") {
        return 0.0189;
      } 
      else if (region == "2tag2pjet_200_350ptv") {
        return 0.1025;
      } 
      else if (region == "2tag2pjet_350_500ptv") {
        return 0.0093;
      } 
      else if (region == "2tag1pfatjet_0addtag_500_750ptv") {
        return 0.0002;
      } 
      else if (region == "2tag1pfatjet_0addtag_750ptv") {
        return 0.0001;
      } 
      else return -1;
    }
    else return -1;
  }
  else return -1;
}


float recoAccbbA(int mA, int ma, const TString &region) {
  if (mA == 1000) {
   if (ma <= 100) { // from 1200,100
	if (region == "2tag2pjet_150_200ptv") {
	  return 0.0034;
	}
	else if (region == "2tag2pjet_200_350ptv") {
	  return 0.0033;
	}
	else if (region == "2tag2pjet_350_500ptv") {
	  return 0.0007;
	}
	else if (region == "2tag1pfatjet_0addtag_500_750ptv") {
	  return 0.0003;
	}
	else if (region == "2tag1pfatjet_0addtag_750ptv") {
	  return 0.;
	}
	else if (region == "3ptag2pjet_150_200ptv") {
	  return 0.0003;
	}
	else if (region == "3ptag2pjet_200_350ptv") {
	  return 0.0008;
	}
	else if (region == "3ptag2pjet_350_500ptv") {
	  return 0.0002;
	}
	else if ((region == "2tag1pfatjet_1paddtag_500_750ptv") || (region == "2tag1pfatjet_1paddtag_750ptv")) {
	  return 0.0002;
	}
	else return -1;
    }
    else if (ma == 200) {
	if (region == "2tag2pjet_150_200ptv") {
	  return 0.0065;
	}
	else if (region == "2tag2pjet_200_350ptv") {
	  return 0.014;
	}
	else if (region == "2tag2pjet_350_500ptv") {
	  return 0.0069;
	}
	else if (region == "2tag1pfatjet_0addtag_500_750ptv") {
	  return 0.0005;
	}
	else if (region == "2tag1pfatjet_0addtag_750ptv") {
	  return 0.;
	}
	else if (region == "3ptag2pjet_150_200ptv") {
	  return 0.0007;
	}
	else if (region == "3ptag2pjet_200_350ptv") {
	  return 0.0027;
	}
	else if (region == "3ptag2pjet_350_500ptv") {
	  return 0.0021;
	}
	else if ((region == "2tag1pfatjet_1paddtag_500_750ptv") || (region == "2tag1pfatjet_1paddtag_750ptv")) {
	  return 0.0004;
	}
	else return -1;    
    }
    else if (ma == 300) {
	if (region == "2tag2pjet_150_200ptv") {
	  return 0.0065;
	}
	else if (region == "2tag2pjet_200_350ptv") {
	  return 0.0211;
	}
	else if (region == "2tag2pjet_350_500ptv") {
	  return 0.0130;
	}
	else if (region == "2tag1pfatjet_0addtag_500_750ptv") {
	  return 0.0004;
	}
	else if (region == "2tag1pfatjet_0addtag_750ptv") {
	  return 0.;
	}
	else if (region == "3ptag2pjet_150_200ptv") {
	  return 0.0007;
	}
	else if (region == "3ptag2pjet_200_350ptv") {
	  return 0.0044;
	}
	else if (region == "3ptag2pjet_350_500ptv") {
	  return 0.0037;
	}
	else if ((region == "2tag1pfatjet_1paddtag_500_750ptv") || (region == "2tag1pfatjet_1paddtag_750ptv")) {
	  return 0.0005;
	}
	else return -1;        
    }
    else if (ma == 400) {    
	if (region == "2tag2pjet_150_200ptv") {
	  return 0.009;
	}
	else if (region == "2tag2pjet_200_350ptv") {
	  return 0.0385;
	}
	else if (region == "2tag2pjet_350_500ptv") {
	  return 0.0193;
	}
	else if (region == "2tag1pfatjet_0addtag_500_750ptv") {
	  return 0.0004;
	}
	else if (region == "2tag1pfatjet_0addtag_750ptv") {
	  return 0.;
	}
	else if (region == "3ptag2pjet_150_200ptv") {
	  return 0.0008;
	}
	else if (region == "3ptag2pjet_200_350ptv") {
	  return 0.0073;
	}
	else if (region == "3ptag2pjet_350_500ptv") {
	  return 0.0053;
	}
	else if ((region == "2tag1pfatjet_1paddtag_500_750ptv") || (region == "2tag1pfatjet_1paddtag_750ptv")) {
	  return 0.0005;
	}
	else return -1;    
    }
    else if (ma == 500) {
	if (region == "2tag2pjet_150_200ptv") {
	  return 0.0138;
	}
	else if (region == "2tag2pjet_200_350ptv") {
	  return 0.0679;
	}
	else if (region == "2tag2pjet_350_500ptv") {
	  return 0.0296;
	}
	else if (region == "2tag1pfatjet_0addtag_500_750ptv") {
	  return 0.0032;
	}
	else if (region == "2tag1pfatjet_0addtag_750ptv") {
	  return 0.;
	}
	else if (region == "3ptag2pjet_150_200ptv") {
	  return 0.0013;
	}
	else if (region == "3ptag2pjet_200_350ptv") {
	  return 0.0124;
	}
	else if (region == "3ptag2pjet_350_500ptv") {
	  return 0.0049;
	}
	else if ((region == "2tag1pfatjet_1paddtag_500_750ptv") || (region == "2tag1pfatjet_1paddtag_750ptv")) {
	  return 0.0005;
	}
	else return -1;        
    }
    else if (ma == 600) {
	if (region == "2tag2pjet_150_200ptv") {
	  return 0.0186;
	}
	else if (region == "2tag2pjet_200_350ptv") {
	  return 0.0893;
	}
	else if (region == "2tag2pjet_350_500ptv") {
	  return 0.0048;
	}
	else if (region == "2tag1pfatjet_0addtag_500_750ptv") {
	  return 0.0002;
	}
	else if (region == "2tag1pfatjet_0addtag_750ptv") {
	  return 0.;
	}
	else if (region == "3ptag2pjet_150_200ptv") {
	  return 0.0013;
	}
	else if (region == "3ptag2pjet_200_350ptv") {
	  return 0.0174;
	}
	else if (region == "3ptag2pjet_350_500ptv") {
	  return 0.0024;
	}
	else if ((region == "2tag1pfatjet_1paddtag_500_750ptv") || (region == "2tag1pfatjet_1paddtag_750ptv")) {
	  return 0.0002;
	}
	else return -1;            
    }
    else return -1;
  }
  else return -1;
}


float xsecBin(const TString &region) {
  if (region == "2tag2pjet_150_200ptv") {
    return 3.26;
  } 
  else if (region == "2tag2pjet_200_350ptv") {
    return 1.47;
  } 
  else if (region == "2tag2pjet_350_500ptv") {
    return 0.33;
  } 
  else if (region == "2tag1pfatjet_0addtag_500_750ptv") {
    return 0.15;
  } 
  else if (region == "2tag1pfatjet_0addtag_750ptv") {
    return 0.05;
  } 
  else if (region == "3ptag2pjet_150_200ptv") {
    return 0.21;
  } 
  else if (region == "3ptag2pjet_200_350ptv") {
    return 0.18;
  } 
  else if (region == "3ptag2pjet_350_500ptv") {
    return 0.06;
  } 
  else if (region == "2tag1pfatjet_1paddtag_500_750ptv") {
    return 0.06;
  } 
  else if (region == "2tag1pfatjet_1paddtag_750ptv") {
    return 0.06;
  } 
  else return -1;
}

float truthAcc(const TString &name, const TString &reg, int ma) {
  TFile *f = TFile::Open(TString::Format("%s/output_0Lep_%s.root", inputPath.Data(), name.Data()), "read");

  TString name_before = TString::Format("hist_0Lep_sig_%s_nCentralJets_Nominal", reg.Data());
  TString name_after = TString::Format("hist_0Lep_sig_%s_nCentralJets_%s_Nominal", reg.Data(), !reg.Contains("1pfat") ? "allcut_reso" : "allcut_merged");
  TH1F *h_before = (TH1F*)f->Get(name_before.Data());
  TH1F *h_after = (TH1F*)f->Get(name_after.Data());
  float before = (h_before) ? h_before->Integral(0,11) : 0;
  float after = (h_after) ? h_after->Integral(0,11) : 0;
  f->Close();
  
  return (before > 0) ? after/before : -1;
}

inline void combine(float &combined_mu, float mu) {
  combined_mu = combined_mu*mu / std::sqrt(std::pow(combined_mu,2) + std::pow(mu, 2));
} 

void printExclusion(TFile *f, TString &name, const float xsec, TH2F *h) {
  // extract masses from name
  auto Strings = name.Tokenize("_");
  auto dsid = ((TObjString*)Strings->At(0))->String();
  auto ss = ((TObjString*)Strings->At(3))->String();
  ss.Remove(TString::EStripType::kLeading, 'm');
  ss.Remove(TString::EStripType::kLeading, 'a');
  int ma = std::stoi(ss.Data());
  ss = ((TObjString*)Strings->At(4))->String();
  ss.Remove(TString::EStripType::kLeading, 'm');
  ss.Remove(TString::EStripType::kLeading, 'X');
  int mx = std::stoi(ss.Data());
  ss = ((TObjString*)Strings->At(2))->String();
  ss.Remove(TString::EStripType::kLeading, 'm');
  ss.Remove(TString::EStripType::kLeading, 'A');
  int mA = std::stoi(ss.Data());
  
  TString name10GeV = name;
  name10GeV.ReplaceAll(TString::Format("mX%d", mx), "mX10");
  name10GeV = (ma != 50) ? name10GeV.ReplaceAll(dsid, std::to_string(200000+ma/100-1)) : name10GeV.ReplaceAll(dsid, "200042");
  
  // Loop over regions
  float combined_mu = 1.E12;
  for (auto r : regions) {
    std::cout << "\tRegion: " << r.Data() << std::endl;
    
    // Get reco-level acceptance
    float rAcc = (useB1) ? recoAcc(mA, ma, r) : recoAccbbA(mA, ma, r);
    
    // Get truth-level acceptance
    TString name_before = TString::Format("hist_0Lep_sig_%s_nCentralJets_Nominal", r.Data());
    TString name_after = TString::Format("hist_0Lep_sig_%s_nCentralJets_%s_Nominal", r.Data(), !r.Contains("1pfat") ? "allcut_reso" : "allcut_merged");
    TH1F *h_before = (TH1F*)f->Get(name_before.Data());
    TH1F *h_after = (TH1F*)f->Get(name_after.Data());
    float before = (h_before) ? h_before->Integral(0,11) : 0;
    float after = (h_after) ? h_after->Integral(0,11) : 0;
    float tAcc = (before > 0) ? after/before : -1;
       
    // Correction for acceptance
    std::cout << "\t\t before corr = " << rAcc << std::endl;
    rAcc *= tAcc/truthAcc((useCorrection)? name10GeV : name, r, ma);
    std::cout << "\t\t after corr = " << rAcc << std::endl;
    std::cout << "\t\t ==> corr = " << tAcc/truthAcc((useCorrection)? name10GeV : name, r, ma) << std::endl;
    
    // Is it excluded?
    float xsec_vis = xsec * 1000 * getBR(ma,mx) * rAcc;
    float xsec_bin = xsecBin(r);
    float mu = xsec_bin/xsec_vis;
    if (mu > 0 && !std::isinf(mu)) combine(combined_mu, mu);
    
    std::cout << "\t\tmu = " << mu << std::endl;
  }
  std::cout << "\t => combined = " << combined_mu << std::endl;
  h->Fill(ma, mx, combined_mu);
}


void TLExclusion() {
  
  TFile *f = TFile::Open("exclusion.root", "recreate");
  
  TH2F *h     = new TH2F("h","", 40,-25,775, 81,-2.5,402.5);
  
  gStyle->SetOptStat(0);
  gStyle->SetPaintTextFormat("3.2f");
  
  for (auto s : (useB1) ? samples_1200 : samples_B2) {
    std::cout << "Sample : " << s.first.Data() << std::endl;
    
    TString fName = TString::Format("%s/output_0Lep_%s.root", inputPath.Data(), s.first.Data());
    TFile *file = TFile::Open(fName, "read");
    
    printExclusion(file, s.first, s.second, h);
        
    file->Close();
  }
      
  TCanvas c;
  TString title = (useB1) ? "m_{A,H,H^{#pm}} = 1200 GeV, tan #beta=1, sin#theta=0.35, #lambda_{3,P1,P2}=3" :
  			    "m_{A,H,H^{#pm}} = 1000 GeV, tan #beta=40, sin#theta=0.7, #lambda_{3,P1,P2}=8";
  h->SetTitle(title);
  h->GetXaxis()->SetTitle("m_{a} [GeV]");
  h->GetYaxis()->SetTitle("m_{#chi} [GeV]");
  h->GetZaxis()->SetRangeUser(0,1.5);
  h->Draw("hcolztext");
  c.Print("exclusion.pdf");   
        
  f->WriteTObject(h);
  f->Close();
}
