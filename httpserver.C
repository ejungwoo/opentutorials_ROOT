void httpserver()
{
    gROOT -> SetBatch(1);
    auto server = new THttpServer("http:8080");
    cout << "http://localhost:8080/" << endl;

    auto cvs = new TCanvas();
    //server -> Register("",cvs);

    auto hist = new TH1D("hist","",100,-10,10);
    hist -> FillRandom("landau");
    hist -> Draw();
}
