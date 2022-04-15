from ast import Num
from re import L
from pydantic import BaseModel, NameEmail,ValidationError, validator

class Users(BaseModel):
    name: str
    username: str
    email: str
    password1:  str
    password2:  str
    role: int

    @validator('name')
    def name_must_contain_space(cls, v):
        if ' ' not in v:
            raise ValueError('must contain a space')
        return v.title()

    @validator('password2')
    def passwords_match(cls, v, values, **kwargs):
        if 'password1' in values and v != values['password1']:
            raise ValueError('passwords do not match')
        return v

    @validator('username')
    def username_alphanumeric(cls, v):
        assert v.isalnum(), 'must be alphanumeric'
        return v

class UsersSignIn(BaseModel):
    username: str
    password1:  str
