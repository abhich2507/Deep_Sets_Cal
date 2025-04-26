void process_root_file(int file_index) {
    // Construct the file name dynamically
    // TString filename = Form("/mnt/c/Users/hnayak/Documents/Proton_Col/result_proton_%d.root", file_index);
    TString filename = Form("/mnt/d/Pion_Col/result_pion_%d.root", file_index);
    TFile *file = TFile::Open(filename);
    
    if (!file || file->IsZombie()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    // Get the tree
    TTree *tree = (TTree*) file->Get("outputTree");  // Ensure tree name is correct
    if (!tree) {
        cout << "Tree not found in file: " << filename << endl;
        return;
    }

    // Declare variables for branches
    vector<double> *Tedep = nullptr;
    Int_t Tevent_id;

    // Set branch addresses
    tree->SetBranchAddress("Tevent_id", &Tevent_id);
    tree->SetBranchAddress("Tedep", &Tedep);

    // Create histogram
    TH1D *Energy = new TH1D("Energy", "Total Energy per Event; Energy (MeV); Events", 100, 0, 30000);
    Energy->GetXaxis()->SetTitle("Energy (MeV)");
    Energy->GetYaxis()->SetTitle("Events");
    Energy->SetTitle("Total Energy Deposition pion");
    Energy->GetXaxis()->SetTitleSize(0.05);
    Energy->GetYaxis()->SetTitleSize(0.05);
    TCanvas *c1 = new TCanvas("c1", "Energy Histogram", 800, 600);

    // Loop over events
    Long64_t nentries = tree->GetEntries();
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        tree->GetEntry(jentry);

        if (!Tedep) continue;  // Skip if null
        
        double sum = 0.0;
        for (size_t i = 0; i < Tedep->size(); i++) {
            sum += Tedep->at(i);
        }

        cout << "Event ID: " << Tevent_id << " | Total Energy: " << sum << endl;
        Energy->Fill(sum);
    }

    // Draw and save histogram
    c1->cd();
    Energy->Draw();
    TString hist_filename = Form("Energy_pion_%d.root", file_index);
    c1->SaveAs(hist_filename);

    // Cleanup
    delete c1;
    file->Close();
}
