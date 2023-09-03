void colors_my_definition()
{
    //new TColor(1201, 0.34509, 0.31372, 0.55294);
    new TColor(1201, 0.0  , 0.247, 0.360);
    new TColor(1202, 0.737, 0.313, 0.564);
    new TColor(1203, 1.0  , 0.388, 0.380);
    new TColor(1204, 1.0  , 0.650, 0.0  );

    //auto cvs = new TCanvas();
    auto cvs = new TCanvas("cvs","paint canvas background");
    //cvs -> SetFillColor(1200);
    cvs -> Divide(2,2);
    for (auto i : {1,2,3,4}) {
        cvs -> cd(i) -> SetFillColor(1200+i);
        cvs -> cd(i) -> Modified();
        cvs -> cd(i) -> Update();
    }

    cvs -> SaveAs("figures/cvs_paint_background.png");
}
