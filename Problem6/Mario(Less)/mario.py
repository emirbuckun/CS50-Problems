def main():            
    i = get_height()         
    for w in range(i):                
        for k in range(i - 1, w, -1):    
            print(" ", end="")              
        for j in range(w + 1):            
            print("#", end="")         
        print()   
        

def get_height():                            
    while True:                            
        try:
            n = int(input("Height: "))         
            if (n >= 1 and n <= 8):             
                break                            
        except:
            print("INVALID")
    return n                                


main()
