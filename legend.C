void legend()
{
    gStyle -> SetTitleFont(132,"");

    auto hist = new TH1D("hist","",120,0,1000);
    for (auto i=0; i< 4*2000; ++i) hist -> Fill(gRandom -> Gaus(123.07, 23.32));
    for (auto i=0; i< 5*2000; ++i) hist -> Fill(gRandom -> Gaus(287.82, 52.18));
    for (auto i=0; i< 3*2000; ++i) hist -> Fill(gRandom -> Gaus(442.34, 51.21));
    for (auto i=0; i<12*2000; ++i) hist -> Fill(gRandom -> Gaus(836.20,171.74));

    double parameters[4][3] = {
        {1000, 143.07, 23.32,},
        { 300, 287.82, 52.18,},
        { 400, 442.34, 51.21,},
        { 500, 736.20,121.74,}, };

    auto fit = new TF1("fit","gaus(0)+gaus(3)+gaus(6)+gaus(9)",0,1000);
    fit -> SetTitle("Total fit");
    for (auto i=0; i<4; ++i) {
        fit -> SetParameter(3*i+0,parameters[i][0]);
        fit -> SetParameter(3*i+1,parameters[i][1]);
        fit -> SetParameter(3*i+2,parameters[i][2]);
    }
    fit -> SetNpx(1000);
    hist -> Fit("fit","RQ0");

    new TColor(1200, 0.0   , 0.2470, 0.3600);
    new TColor(1201, 0.3450, 0.3130, 0.5520);
    new TColor(1202, 0.7370, 0.3130, 0.5640);
    new TColor(1203, 1.0   , 0.3880, 0.3800);
    new TColor(1204, 1.0   , 0.6500, 0.0   );
    new TColor(1205, 1.0   , 0.6500, 0.0   );
    //new TColor(1205, 0.9412, 0.9412, 0.5569);
    new TColor(1206, 0.5686, 0.7922, 0.3843);
    new TColor(1207, 0.2784, 0.5020, 0.4667);
    new TColor(1208, 0.2275, 0.2824, 0.4549);
    new TColor(1209, 0.9412, 0.9137, 0.8235);


    //

    auto cvs = new TCanvas("cvs","",800,600);
    auto frame = new TH2D("frame","Energy Loss;Energy Loss;Count",100,0,1000,100,0,1250);
    frame -> GetXaxis() -> SetLabelFont(132);
    frame -> GetYaxis() -> SetLabelFont(132);
    frame -> GetXaxis() -> SetTitleFont(132);
    frame -> GetYaxis() -> SetTitleFont(132);
    frame -> GetXaxis() -> SetTitleOffset(1.2);
    frame -> GetYaxis() -> SetTitleOffset(1.5);
    frame -> SetStats(0);
    frame -> Draw();

    for (auto i=0; i<4; ++i) {
        auto ampl = fit -> GetParameter(3*i+0);
        auto mean = fit -> GetParameter(3*i+1);
        auto sigm = fit -> GetParameter(3*i+2);
        parameters[i][0] = ampl;
        parameters[i][1] = mean;
        parameters[i][2] = sigm;
        auto fit_particle = new TF1(Form("fit_particle_%d",i),"gaus(0)",mean-4*sigm,mean+4*sigm);
        fit_particle -> SetTitle(Form("Particle %d",i));
        fit_particle -> SetParameters(ampl,mean,sigm);
        fit_particle -> SetLineWidth(6);
        fit_particle -> SetLineColor(1205+i);
        fit_particle -> Draw("samel");
    }

    for (auto i=0; i<4; ++i) {
        auto line = new TLine(parameters[i][1],0,parameters[i][1],1250);
        //line -> SetName(Form("Particle %d mean",i));
        line -> SetLineColor(1205+i);
        line -> SetLineStyle(2);
        line -> Draw();
    }
    fit -> SetLineWidth(3);
    fit -> Draw("samel");

    auto graph = new TGraphErrors();
    for (auto bin=0; bin<120; ++bin) {
        graph -> SetPoint(bin, hist->GetBinCenter(bin), hist->GetBinContent(bin));
        graph -> SetPointError(bin, 0, hist->GetBinError(bin));
    }
    graph -> SetTitle("Data");
    graph -> SetLineColor(kBlack);
    graph -> SetMarkerColor(kBlack);
    graph -> SetMarkerStyle(24);
    graph -> SetMarkerSize(0.55);

    auto x1 = cvs->GetUxmin() + cvs->GetLeftMargin();
    auto x2 = cvs->GetUxmax() - cvs->GetRightMargin();
    auto y1 = cvs->GetUymin() + cvs->GetBottomMargin();
    auto y2 = cvs->GetUymax() - cvs->GetTopMargin();

    auto mlLength = cvs->GetLeftMargin()   / (x2 - x1) * 1000;
    auto mrLength = cvs->GetRightMargin()  / (x2 - x1) * 1000;
    auto mbLength = cvs->GetBottomMargin() / (y2 - y1) * 1250;
    auto mtLength = cvs->GetTopMargin()    / (y2 - y1) * 1250;

    graph -> Draw("same p");

    auto arrow1 = new TArrow(-mlLength,100,0,100);
    auto arrow2 = new TArrow(1000,100,1000+mrLength,100);
    auto arrow3 = new TArrow(750,-mbLength,750,0);
    auto arrow4 = new TArrow(750,1250,750,1250+mtLength);
    for (auto arrow : {arrow1, arrow2, arrow3, arrow4})
    {
        arrow -> SetArrowSize(0.025);
        arrow -> SetLineWidth(2);
        arrow -> Draw("<->");
    }

    auto legend = cvs -> BuildLegend(x1+0.35,y1+0.450,x2,y2);
    legend -> SetTextFont(132);
    legend -> SetNColumns(2);
    legend -> Draw();
}
