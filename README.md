# subsum
just a subroutine in C for the maximum subarray sum problem

This subroutine works by merging together consecutive elements of the array.
It merges consecutive "sums" of the same sign and also some special cases of mixed sign little subgroups ("triples" in the code).
the proof that this works is kinda long winded, but you can prove by contradiciton that after the whole  list has been "processed" the max element is the (or one of?) the maximum subarrays
The main idea is to look at the array composed of the absolute value of our list elements. no further merging should allow us to find a better result.
i can give an explanatin that makes sense if someone asks for it.
refutations are welcome
