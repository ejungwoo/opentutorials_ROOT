void colors_usage_example()
{
    //auto cvs = new TCanvas("cvs_color_usage","color usage",600,450);
    auto cvs = new TCanvas("cvs_color_usage","color usage",600*2,450*2);
    double x[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    double y[] = {1, 4, 6, 7, 7.5, 7.5, 7, 6, 4, 1};
    TGraph* graph = new TGraph(10,x,y);
    graph -> SetMarkerStyle(20);
    graph -> SetMarkerSize(4);
    graph -> SetLineWidth(6);

    graph -> SetLineColor(kBlue+2);
    graph -> SetMarkerColor(kOrange+10);
    graph -> SetFillColor(kSpring+1);

    graph -> Draw("aplf");

    //graph -> SetTitle("colors usage example");
    graph -> SetTitle("");
    gPad -> SaveAs("figures/colors_usage_example.png");
}
