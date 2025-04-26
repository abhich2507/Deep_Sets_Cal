void sum_energy() {
    TTree          *fChain;   //!pointer to the analyzed TTree or TChain
    Int_t           fCurrent; //!current Tree number in a TChain
    // Open the ROOT file
    TFile *file = TFile::Open("/mnt/c/Users/hnayak/Documents/Proton_Col/result_proton_1.root");  
    if (!file || file->IsZombie()) {
        cout << "Error opening file!" << endl;
        return;
    }

    // Get the tree
    TTree *tree = (TTree*) file->Get("outputTree");  // Replace with actual tree name
    if (!tree) {
        cout << "Tree not found!" << endl;
        return;
    }
    Int_t           Tevent_id;
    std::vector<double>  *Tedep;
    TBranch        *b_Tevent_id;   //!
    TBranch        *b_Tedep;   //!
    Tedep = 0;
    if (!tree) return;
   fChain = tree;
   fCurrent = -1;
  

   fChain->SetBranchAddress("Tevent_id", &Tevent_id, &b_Tevent_id);
   fChain->SetBranchAddress("Tedep", &Tedep, &b_Tedep);

    //histogram
    TH1D *Energy = new TH1D("Energy","Energy",1000,0,30000);
    TCanvas *c1 = new TCanvas("c1","c1",800,600);

    TH1D *Energy = new TH1D("Energy","Energy",1000,0,30000);
    TCanvas *c1 = new TCanvas("c1","c1",800,600);
   
      if (fChain == 0) return;
   
      Long64_t nentries = fChain->GetEntriesFast();
   
      Long64_t nbytes = 0, nb = 0;
      for (Long64_t jentry=0; jentry<nentries;jentry++) {
         Long64_t ientry = LoadTree(jentry);
         if (ientry < 0) break;
         nb = fChain->GetEntry(jentry);   nbytes += nb;
         // if (Cut(ientry) < 0) continue;
      double sum=0.;
        int size=Tedep->size();
         for (int i=0; i<size; i++)
         {  //cout<<"Tevent_id: "<<Tevent_id<<endl;
         //    cout<<Tedep->at(i)<<endl;
            sum+=Tedep->at(i);
         }
         cout<<Tevent_id<<endl;
         cout<<"sum: "<< sum<< endl;
         Energy->Fill(sum);
      }
      c1->cd();  
      Energy->Draw();
      c1->SaveAs("Energy1.root");

    // double energy_sum = 0;
    // // Variables to store vector data
    // for (int jentry=0; jentry<tree->GetEntries(); jentry++) {
    // // Load the entry
    // fChain->GetEntry(jentry);
    

    // // Set branch addresses
    // tree->SetBranchAddress("Tevent_id", &Tevent_id);
    // tree->SetBranchAddress("Tedep", &Tedep);


    // // cout<<"Tevent_id: "<<Tevent_id<<endl;
    // // cout<<"Tedep: "<<Tedep->at(jentry)<<endl;
    // energy_sum += Tedep->at(jentry);
    // // Create a map to sum Tedep for each event_id
   
    // }
    // cout<<"sum: "<<energy_sum<<endl;
    // Energy->Fill(energy_sum);  
    // c1->cd();
    // Energy->Draw();
    // c1->SaveAs("Energy1.root"); 
    }

    
