from email.policy import HTTP
import os
from fastapi import FastAPI,HTTPException
from pydantic import BaseModel, NameEmail
from deta import Deta
from models import Users, UsersSignIn
from dotenv import load_dotenv

load_dotenv()  # take environment variables from .env.

deta = Deta(os.environ.get("DETA_PROJECT_KEY"))

#tables
db_user = deta.Base("users")
db_candidates = deta.Base("candidates")


app = FastAPI()

@app.get("/")
async def helloworld():
    return "Hello World"

@app.post("/signup")
async def newUser(sub:Users):
    existuser = db_user.fetch({"email": sub.email})
    if(existuser._items):
        raise  HTTPException(403,'user with same email ID exists!')  
    if('@' not in sub.email or '.' not in sub.email ) :
        raise  HTTPException(403,'emailid not valid!') 
    if(sub.role not in [0,1,2]) :
        raise  HTTPException(403,'role not valid!')       
    user = db_user.put({
        "name": sub.name,
        "username": sub.username,
        "email": sub.email,
        "password": sub.password1,
        "role": sub.role,
    })
    
    return user["key"]

@app.post("/signin")
async def login(sub:UsersSignIn):
    curruser = db_user.fetch({"username": sub.username,"password": sub.password1})
    if(curruser._items):
        return curruser._items[0]["key"]
    else:
        return "authentication failed"

