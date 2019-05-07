#    Jupiter
  _**Find Your Frequency**_

![Jupiter's Magnetic Field](https://www.spaceanswers.com/wp-content/uploads/2014/06/Thumb.jpg)



### Problem

_**A lot of dating applications available today have developed reputations that limit the demographic**_ to first and second year college students (18-22). Beyond that age, many don't like to disclose the fact that they are on Tinder, Bumble, etc

_**No dating applications available today have addressed the anxiety associated with meeting a stranger**_, particularly in an online setting. We don't always bond with people well online. There is no oppurtunities to have a [Shared Emotional Experience](https://en.wikipedia.org/wiki/Social_sharing_of_emotions#Effect_on_relationships)

_**All dating applications available today provide minimal effort in assessing matches and guiding users**_ in the dating process. No effort in a personality assesment or education in attraction, love, relationships, etc

* **People need discretion**
* **People need to be assessed**
* **People need to be coached and pushed**


## Discretion
**_This is an easier obstacle_** we could use [Facebook's API to find a user's friends](https://developers.facebook.com/docs/graph-api/reference/user/friends/) and block them from the users feed, by default. User can request to undo "Icognito".

**What if I wouldn't mind some of the girls I have as Friends on Facebook in my Jupiter Feed?** We query for the "Facebook-Friends", store that in an array on Server-Side. Each "Potential-Match" could have:
```javascript
{
...
friendsOnSocialMedia = true
}
```
That way when I'm swiping around and encounter a Facebook-Friend the picture and name is blurred and I can click "Take a chance" to request to reveal their identity if they agree to "Take a chance". In the case that the girl that I happen to be connected with on social media has "Icognito" disabled, I would still be able to see her identity without her being able to see mine.

**Another aspect of discretion is what might my new girlfriend find on my phone** apart from secrecy from friends on social media, there's also discretion from friends who might know my passcode on my phone -- I trust them enough to let them use my phone but when they open my Jupiter I don't want them to see the things I've said to matches, or to see the photos I've chosen to display. This is why Users will set a "Jupiter Passcode" that will prompt each time the app [goes into the background](https://facebook.github.io/react-native/docs/appstate)

**My Girl is going to know my Jupiter Passcode** so we model the Chat-Client after Snapchat's. Messages are not saved, they dissappear unless the User saves the text [with a long press](https://reactnativecode.com/add-onlongpress-on-button-example/)



## Education

**Theories on Personality are qualitative, undeveloped, and constantly changing** [there are a variety of Personality Assesment Instruments (PAI) widely in use by individuals and institutions](https://courses.lumenlearning.com/boundless-psychology/chapter/assessing-personality/) most notably the Myers-Briggs Type Indicator (MBTI) which is the most widely used PAI across industry. The MBTI was created by two individuals that were outside of the field of Psychology and not formal researchers in the field of Personality Psychology.

We need to research this area, build a model for our PAI using current research. [These are some of the PAIs](https://courses.lumenlearning.com/boundless-psychology/chapter/assessing-personality/).

We will assign everyone a "Frequency" that they can look at, this will be determined by their "Pace" and "Seriousness". It will be initialized at sign-up and will change based on a user's behaviour in the application.

Someone with low-pace has nothing to do most of the time, they live slower -- someone with high-pace is always meeting friends, working, or training. High-pace individuals are busy. This can be determined from occupational questions, querying social media activity, asking how often they hangout with friends or family, etc. As well as tracking people's activity level on the application -- low-pace people will always be on, and will tend to have higher word counts and send messages more frequently.

Someone with low-seriousness is immature, low socioeconomic status, and not influential -- a high-seriousness individual will have a higher salary, work in a more respected industry, but more importantly is how they speak. [Eloquence](https://en.wikipedia.org/wiki/Eloquence) is the biggest factor to someone's seriousness. Since speech is a product of thought, we should see more conviction in their exchanges; their diction will be novel with brevity and good grammar. We don't set AutoCorrect, we monitor grammar and punctuality mistakes, letters-per-word, and determine the uniqueness of the words they choose. This will reflect in their seriousness score.

Pace will be represented by the wavelength, Seriousness will be represented by the amplitude.
![Wave](http://www.sengpielaudio.com/WavesSinusodialTimeDistance.gif)


## Moderation
_**Jupiter needs to function as a moderator between relationships**_ instead of functioning as a broker. The application needs to be more involved in how any two individuals interact. Starting with a chat-client to enable sending messages, the first thing would be to reimagine how we send text-messages. Messages that are recieved will not show a sneakpeak, similar to Snapchat, you click the users avatar to view the message. Instead of opening a chat box, it will open an area which contains a message, rather than having discrete "message-units", and from there we will provide the user with options that ask how the message made them feel, how they think that other person is thinking, anything that gets them to critically-think about the exchange in an objective manner, eg "Do you believe she's being dismissive?" (which we could somewhat predict by tracking changes in message frequency and wordcount / eloquence -- people speak with more power when in an emotional conflict in most cases) so we can provide objective guidance with listing common reasons for these kinds of behaviors, depending on our research efforts in the relevant academia.

_**Urging people to take action is paramount**_ but they are nervous with strangers. We need to come up with ways to help break the ice between people, ease them into conversation. We need a way of measuring the quality of the relationship, how do we programmatically determine how well things are going between two individuals? Worth some thought. That way we know when to apply the pressure on them to move a step foreword, eg pull movie tickets and have them accept or decline (something like that).

# Checkpoints

## CLIENT SIDE

### USER INTERFACE
  - [] **LOGIN_SIGNUP COMPONENT (LSC)**
    - [] MOBILE
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
    - [] DESKTOP
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
    - [] ANDROID / IOS
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
        
  - [] **PAI_TEST COMPONENT (PTC)**
    - [] MOBILE
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
    - [] DESKTOP
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
    - [] ANDROID / IOS
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
        
  - [] **MAIN_DASHBOARD COMPONENT (MDC)**
    - [] MOBILE
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
    - [] DESKTOP
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
    - [] ANDROID / IOS
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
    
  - [] **PROFILE_SETTINGS COMPONENT (PSC)**
    - [] MOBILE
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
    - [] DESKTOP
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
    - [] ANDROID / IOS
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
    
  - [] **VIEW_MATCHES COMPONENT (VMC)**
    - [] MOBILE
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
    - [] DESKTOP
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
    - [] ANDROID / IOS
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
    
  - [] **SEARCH_FEED COMPONENT (SFC)**
    - [] MOBILE
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
    - [] DESKTOP
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
    - [] ANDROID / IOS
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
    
  - [] **PROFILE_VIEW COMPONENT(PVC)**
    - [] MOBILE
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
    - [] DESKTOP
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
    - [] ANDROID / IOS
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
      
  - [] **PERSONALITY_FREQUENCY COMPONENT (PFC)**
    - [] MOBILE
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
    - [] DESKTOP
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
    - [] ANDROID / IOS
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
    
  - [] **SINGLE_USER_CHAT COMPONENT (PFC)**
    - [] MOBILE
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
    - [] DESKTOP
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
    - [] ANDROID / IOS
      - [] _DESIGNED_
      - [] _IMPLEMENTED_
      
### DATA INTEGRATION

**_TBA_**
  
  
# SERVER SIDE
  - [] **_Reverse Proxy Balancer (RPB)_**
    - [] TLS 1.3 Authentication
    - [] Cache
    
  - [] **_Web-Server API_ (WSA)**
    - [] User-Datagram Protocol (UDP) w/ RPB
    - [] Routes
    - [] Controller
      
  - [] **Database
    - [] Instance Running
    - [] Model Conception Created
    - [] Model Implemented
    
  - [] **Database-Proxy-Server
    - [] Connected to Database Instance
    - [] Connected to Web-Server
    - [] In-Memory Database
      - [] Modeled
      - [] Implemented
    - [] Complete REST API
      - [] Modeled
      - [] Implemented
  
