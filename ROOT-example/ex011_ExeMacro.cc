{
  TGraph *g = new TGraph();               // Definition of TGraph class "g", call empty constructor
  g->SetPoint(0,1.,1.1);                  // Set 1st point (X=1., Y=1.1)
  g->SetPoint(1,2.,1.9);                  // Set 2nd point (X=2., Y=1.9)
  g->SetPoint(2,3.,3.0);                  // Set 3rd point (X=3., Y=3.0)
  g->SetPoint(3,4.,3.9);                  // Set 4th point (X=4., Y=3.9)
  g->SetMarkerStyle(20);                  // Set Marker Style (filled circule)

  TCanvas *c1 = new TCanvas("c1","c1");   // Definition of TCanvas class "c1", name="c1", title="c1"
  g->Draw("APL");                         // Draw "g" as an option "A(Draw Axis) & P(Draw Point) & L (Draw Line)"
}
