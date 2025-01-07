from qnapstats import QNAPStats
from pprint import pprint

# pip3 install qnapstats
# https://github.com/colinodell/python-qnapstats?tab=readme-ov-file#usage-example
qnap = QNAPStats('NAS00A2D4.local', 8080, 'home-assistant', 'XXX')

pprint(qnap.get_system_stats())
pprint(qnap.get_system_health())
pprint(qnap.get_smart_disk_health())
pprint(qnap.get_volumes())
pprint(qnap.get_bandwidth())
