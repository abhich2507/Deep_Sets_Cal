void merge_histograms(int num_files = 10) {
    TH1D *h_sum = nullptr; // Pointer for the summed histogram

    for (int i = 1; i <= num_files; i++) {
        TString filename = Form("Energy_pion_%d.root", i);
        TFile *file = TFile::Open(filename);

        if (!file || file->IsZombie()) {
            cout << "Error opening file: " << filename << endl;
            continue;
        }

        TCanvas *c1 = (TCanvas*) file->Get("c1");
        if (!c1) {
            cout << "Canvas 'c1' not found in " << filename << endl;
            file->Close();
            continue;
        }

        TH1D *h_temp = (TH1D*) c1->GetListOfPrimitives()->FindObject("Energy");
        if (!h_temp) {
            cout << "Histogram 'Energy' not found in " << filename << endl;
            file->Close();
            continue;
        }

        if (!h_sum) {
            h_sum = (TH1D*) h_temp->Clone("h_sum");
            h_sum->SetDirectory(0); // Detach from file
        } else {
            h_sum->Add(h_temp);
        }

        file->Close();
    }

    if (h_sum) {
        TCanvas *c_merged = new TCanvas("c_merged", "Merged Histogram", 800, 600);
        h_sum->Draw();
        c_merged->SaveAs("Merged_Histogram_pion.root");
        c_merged->SaveAs("Merged_Histogram_pion.png"); // Optional
    } else {
        cout << "No histograms merged!" << endl;
    }
}
