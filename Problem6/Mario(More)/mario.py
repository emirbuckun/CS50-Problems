def main():            
    i = get_height()         
    for w in range(i):                
        for j in range(i - 1, w, -1):    
            print(" ", end="")              
        for k in range(w + 1):            
            print("#", end="")    
        for l in range(2):    
            print(" ", end="")              
        for m in range(w + 1):            
            print("#", end="")
        print()   
        

def get_height():                            
    while True:                            
        try:
            n = int(input("Height: "))         
            if (n >= 1 and n <= 8):             
                break                            
        except:
            print("INVALİD")
    return n                                


main()
