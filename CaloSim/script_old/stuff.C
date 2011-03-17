  leg = new TLegend(0.6,0.7,0.89,0.89);  
  leg->AddEntry(hxd1,"center+nearest neighbors","l");
  leg->AddEntry(hxd2,"cent+NN+next nearest neighbors","l");
  leg->Draw();



  leg = new TLegend(0.6,0.7,0.89,0.89);  
  leg->AddEntry(hi,"center","l");
  leg->AddEntry(h1,"nearest neighbors","l");
  leg->AddEntry(h2,"next nearest neighbors","l");
  leg->Draw();
