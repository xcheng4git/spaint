//###
#if 1

#include <iostream>

#include <infermous/engines/MeanFieldInferenceEngine.h>
using namespace infermous;

typedef int Label;

struct PPC : PairwisePotentialCalculator<Label>
{
  float calculate_potential(const Label& l1, const Label& l2) const
  {
    return l1 == l2 ? 0.0f : 1.0f;
  }
};

int main()
{
  PotentialsGrid_Ptr<Label> unaries(new PotentialsGrid<Label>(5, 5));

  std::map<Label,float> pixelUnaries;
  for(int i = 0; i < 5; ++i)
  {
    pixelUnaries.insert(std::make_pair(i, 0.5f));
  }

  for(size_t i = 0; i < 5; ++i)
    for(size_t j = 0; j < 5; ++j)
    {
      (*unaries)(i,j) = pixelUnaries;
    }

  CRF2D_Ptr<Label> crf(new CRF2D<Label>(unaries, boost::shared_ptr<PPC>(new PPC)));
  std::cout << *crf << '\n';

  MeanFieldInferenceEngine<Label> mfie(crf, CRFUtil::make_circular_neighbour_offsets(3));

  mfie.update_crf();
  std::cout << *crf << '\n';

  mfie.update_crf();
  std::cout << *crf << '\n';

  std::cout << crf->predict_labels() << '\n';

  return 0;
}

#endif
