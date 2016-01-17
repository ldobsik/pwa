function [base]=pwa_base(g)
% construct a vector base consisting of triangular elements on the input grid
% the base is represented by a sparse vector

  M = length(g);
  N = g(end)-g(1)+1;

  col = 1;
  row = g(1)+1;
  base = sparse ([row],[col],[1],N,M);  %init first row

  for m = diff(g)'
    base((row+1):(row+m),col:(col+1)) = ([(m-1):-1:0; 1:m]/m)';
    col = col + 1;
    row = row + m;
  end

end
