from graphillion import GraphSet
import graphillion.tutorial as tl

GraphSet.set_universe(tl.grid(6, 6))
S, G = 1, 49
P = GraphSet.paths(S, G)
print(len(P))
