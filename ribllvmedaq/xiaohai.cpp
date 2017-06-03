#include "TApplication.h"
#include "TDAQApplication.h"
#include "TConfig.h"
#include "TDataFileReader.h"
#include "TDataAnalyser.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TSystem.h"
#include "TMath.h"
#include "TVector3.h"
#include "TROOT.h"
#include "TApplication.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TFormula.h"
#include "TProfile.h"
#include "TNtuple.h"
#include "TRandom.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TStyle.h"
#include "TText.h"
#include "TLatex.h"
#include "TLine.h"
#include "TPad.h"
#include "TObjArray.h"
#include "TTree.h"
#include "TBranch.h"
#include "TStopwatch.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TFrame.h"
#include "TF1.h"
#include "TMinuit.h"

#include "TBoard.h"
#include "TModV830AC.h"
#include "TModV785.h"
#include "TModV785N.h"
#include "TModV775.h"
#include "TModV775N.h"
#include "TModV792.h"


#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <map>
#include<cstdlib>

using namespace std;

TH2D *testhis = new TH2D("testhis", "testhis", 200, 0, 4000, 200, 0, 4000);

int main(int argc,char **argv)
{
  TFile *file = new TFile("../2016gdr0524.root");
  TTree *fChain = (TTree*)file->Get("RawData;4");//fChain can be a TChain

  Int_t nentries;
  nentries=(Int_t)fChain->GetEntries();
  cout<<"All the entry number: "<<nentries<<endl;

  TBranch *bran103 = 0;
  TBranch *bran104 = 0;
  TBranch *bran106 = 0;
  TBranch *bran108 = 0;
  TBranch *bran110 = 0;
  TBranch *bran112 = 0;
  TBranch *bran114 = 0;
  TBranch *bran116 = 0;
  TBranch *bran118 = 0;
  TBranch *bran120 = 0;

  TModV830AC *vmod103 = new TModV830AC(); //
  TModV785 *vmod104 = new TModV785();	//Si1 60um
  TModV785 *vmod106 = new TModV785();	//Si2 60um
  TModV785 *vmod108 = new TModV785();	//Si4 100um
  TModV785 *vmod110 = new TModV785();	//QSD 300um
  TModV785 *vmod112 = new TModV785();	//
  TModV785N *vmod114 = new TModV785N();
  TModV775N *vmod116 = new TModV775N();
  TModV775 *vmod118 = new TModV775();
  TModV775 *vmod120 = new TModV775();

  fChain->SetBranchAddress("Mod103_TModV830AC",&vmod103,&bran103);
  fChain->SetBranchAddress("Mod104_TModV785",&vmod104,&bran104);
  fChain->SetBranchAddress("Mod106_TModV785",&vmod106,&bran106);
  fChain->SetBranchAddress("Mod108_TModV785",&vmod108,&bran108);
  fChain->SetBranchAddress("Mod110_TModV785",&vmod110,&bran110);
  fChain->SetBranchAddress("Mod112_TModV785",&vmod112,&bran112);
  fChain->SetBranchAddress("Mod114_TModV785N",&vmod114,&bran114);
  fChain->SetBranchAddress("Mod116_TModV775N",&vmod116,&bran116);
  fChain->SetBranchAddress("Mod118_TModV775",&vmod118,&bran118);
  fChain->SetBranchAddress("Mod120_TModV775",&vmod120,&bran120);

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
      Long64_t ientry = fChain->LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);
      nbytes += nb;

      /// some tests
      if (vmod108->chdata[25] > 500 && vmod108->chdata[26] > 500)
	{
	  testhis->Fill(vmod108->chdata[26], vmod108->chdata[25]);
	}
      // for (int i = 0; i != vmod104->MaxChannel; ++i)
      // 	{
	 
      // 	}
    }
  TFile *saveFile = new TFile("saveFile.root", "RECREATE");
  testhis->Write();
  saveFile->Write();

  return 0;

}
