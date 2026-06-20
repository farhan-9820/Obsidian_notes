Instead of searching through every name linearly, the system passes the name through a hash function, which spits out an exact index number (e.g., "John Smith" = Slot 14). The system goes directly to Slot 14. This turns searching from a slow process into an instantaneous one *($O(1)$ time complexity).*

