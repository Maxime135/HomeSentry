import UIKit

// Replace with your ThingSpeak Channel ID and API Key
let channelID = ""
let apiKey = ""


// Define the ThingSpeak API URL
let urlString = "https://api.thingspeak.com/channels/\(channelID)/feeds.json?api_key=\(apiKey)"

// Example JSON with object root:
/*
    {
         "channel": {
             "id": 2350211,
             "name": "HomeSentry",
             "latitude": "45.777126435",
             "longitude": "3.0872824455",
             "field1": "Temperature1",
             "field2": "Pressure1",
             "created_at": "2023-11-19T11:01:01Z",
             "updated_at": "2023-12-02T20:57:37Z",
             "last_entry_id": 48
           },
         "feeds": [
           {
             "created_at": "2023-12-02T21:01:05Z",
             "entry_id": 1,
             "field1": "20.20000",
             "field2": null
           }],
    }
*/


// Define the nested dictionary structure
struct ChannelDictionary: Decodable {
    let id: Int
    let name: String
    let latitude: String
    let longitude: String
    let field1: String
    let field2: String
    let created_at: String
    let updated_at: String
    let last_entry_id: Int
}

struct ItemData: Decodable {
    let created_at: String
    let entry_id: Int
    let field1: String?
    let field2: String?
}

// Define the structure of the JSON file to parse
struct ThingSpeakData: Decodable {
    let channel: ChannelDictionary
    let feeds: [ItemData]
    
}




// Perform the API request and fetch data
func fetchData() {
    guard let url = URL(string: urlString) else {
        print("Invalid URL")
        return
    }

    URLSession.shared.dataTask(with: url) { (data, response, error) in
        
        if let data = data {
            do {
                let decoder = JSONDecoder()

                
                let result = try decoder.decode(ThingSpeakData.self, from: data)
                
                
                for element in result.feeds {
                    print("Temperature: \(element.field1) °C")
                    print("Pressure: \(element.field1) Pa")
                }
                
            } catch {
                print("Error decoding JSON: \(error)")
            }
        }
    }.resume()
}

// Call the fetchData function
fetchData()



