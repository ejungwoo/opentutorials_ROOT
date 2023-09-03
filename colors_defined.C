void DrawMyTable();

void colors_defined()
{
    TCanvas* cvs_ct = new TCanvas("cvs_ct","color table",50,100,500,200);
    cvs_ct -> DrawColorTable();
    //DrawMyTable();

    TColorWheel* cw = new TColorWheel();
    TCanvas* cvs_cw = new TCanvas("cvs_cw","color wheel",600,100,600,600);
    cw -> SetCanvas(cvs_cw);
    cw -> Draw();

    cvs_ct -> SaveAs("figures/color_table.png");
    cvs_cw -> SaveAs("figures/color_wheel.png");
}

void DrawMyTable()
{
    double imax = 10;
    double jmax = 10;
    double ttsize = 0.035;

    TCanvas *cvs_ct = new TCanvas("cvs_ct","color table",50,100,50*imax,40*jmax);

    Int_t i, j;
    Int_t color;
    Double_t xlow, ylow, xup, yup, hs, ws;
    Double_t x1, y1, x2, y2;
    x1 = y1 = 0;
    x2 = y2 = 20;

    gPad->SetFillColor(0);
    gPad->Clear();
    gPad->Range(x1,y1,x2,y2);

    TText text(0,0,"");
    text.SetTextFont(61);
    text.SetTextSize(ttsize);
    text.SetTextAlign(22);

    TBox box;

    // Draw color table boxes.
    hs = (y2-y1)/Double_t(jmax);
    ws = (x2-x1)/Double_t(imax);
    for (i=0;i<imax;i++) {
        xlow = x1 + ws*(Double_t(i)+0.1);
        xup  = x1 + ws*(Double_t(i)+0.9);
        for (j=0;j<jmax;j++) {
            ylow = y1 + hs*(Double_t(j)+0.1);
            yup  = y1 + hs*(Double_t(j)+0.9);
            color = imax*j + i;
            box.SetFillStyle(1001);
            box.SetFillColor(color);
            box.DrawBox(xlow, ylow, xup, yup);
            box.SetFillStyle(0);
            box.SetLineColor(1);
            box.DrawBox(xlow, ylow, xup, yup);
            if (color == 1) text.SetTextColor(0);
            else            text.SetTextColor(1);
            text.DrawText(0.5*(xlow+xup), 0.5*(ylow+yup), TString::Format("%d",color).Data());
        }
    }
}
